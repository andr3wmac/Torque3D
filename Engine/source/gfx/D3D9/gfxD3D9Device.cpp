//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Partial refactor by: Anis A. Hireche (C) 2014 - anishireche@gmail.com
//-----------------------------------------------------------------------------

#include "console/console.h"
#include "core/stream/fileStream.h"
#include "core/strings/unicode.h"
#include "core/util/journal/process.h"
#include "gfx/D3D9/gfxD3D9Device.h"
#include "gfx/D3D9/gfxD3D9CardProfiler.h"
#include "gfx/D3D9/gfxD3D9VertexBuffer.h"
#include "gfx/D3D9/gfxD3D9EnumTranslate.h"
#include "gfx/D3D9/gfxD3D9QueryFence.h"
#include "gfx/D3D9/gfxD3D9OcclusionQuery.h"
#include "gfx/D3D9/gfxD3D9Shader.h"
#include "gfx/D3D9/gfxD3D9Target.h"
#include "gfx/D3D9/gfxD3D9ScreenShot.h"
#include "platformWin32/platformWin32.h"
#include "windowManager/win32/win32Window.h"
#include "windowManager/platformWindow.h"
#include "gfx/screenshot.h"
#include "materials/shaderData.h"

#pragma comment(lib, "d3d9.lib")

/* 
	Anis -> NOTE:
	NVIDIA PerfHUD support has been removed because deprecated in favor of nvidia nsight which it doesn't require a special flag device for usage.
*/

GFXAdapter::CreateDeviceInstanceDelegate GFXD3D9Device::mCreateDeviceInstance(GFXD3D9Device::createInstance);

GFXDevice *GFXD3D9Device::createInstance( U32 adapterIndex )
{
   LPDIRECT3D9EX d3d9;
   
   HRESULT hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &d3d9);
   
   if(FAILED(hr))
	   AssertFatal(false, "Direct3DCreate9Ex call failure");

   GFXD3D9Device* dev = new GFXD3D9Device(d3d9, adapterIndex);
   return dev;
}

GFXFormat GFXD3D9Device::selectSupportedFormat(GFXTextureProfile *profile, const Vector<GFXFormat> &formats, bool texture, bool mustblend, bool mustfilter)
{
	DWORD usage = 0;

	if(profile->isDynamic())
		usage |= D3DUSAGE_DYNAMIC;

	if(profile->isRenderTarget())
		usage |= D3DUSAGE_RENDERTARGET;

	if(profile->isZTarget())
		usage |= D3DUSAGE_DEPTHSTENCIL;

	if(mustblend)
		usage |= D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING;

   if(mustfilter)
		usage |= D3DUSAGE_QUERY_FILTER;

	D3DDISPLAYMODEEX mode;
	ZeroMemory(&mode, sizeof(mode));
	mode.Size = sizeof(mode);

	HRESULT hr = mD3D->GetAdapterDisplayModeEx(mAdapterIndex, &mode, NULL);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "Unable to get adapter mode.");
	}

	D3DRESOURCETYPE type;
	if(texture)
		type = D3DRTYPE_TEXTURE;
	else
		type = D3DRTYPE_SURFACE;

	for(U32 i=0; i < formats.size(); i++)
	{
		if(mD3D->CheckDeviceFormat(mAdapterIndex, D3DDEVTYPE_HAL, mode.Format, usage, type, GFXD3D9TextureFormat[formats[i]]) == D3D_OK)
			return formats[i];
	}

	return GFXFormatR8G8B8A8;
}

D3DPRESENT_PARAMETERS GFXD3D9Device::setupPresentParams(const GFXVideoMode &mode, const HWND &hwnd) const
{
	D3DPRESENT_PARAMETERS d3dpp; 
	D3DFORMAT fmt = GFXD3D9TextureFormat[GFXFormatR8G8B8X8]; // 32bit format

	if(mode.bitDepth == 16)
		fmt = GFXD3D9TextureFormat[GFXFormatR5G6B5]; // 16bit format

	D3DMULTISAMPLE_TYPE aatype;
	DWORD aalevel;

	// Setup the AA flags...  If we've been ask to 
	// disable  hardware AA then do that now.
	if(mode.antialiasLevel == 0 || Con::getBoolVariable( "$pref::Video::disableHardwareAA", false))
	{
		aatype = D3DMULTISAMPLE_NONE;
		aalevel = 0;
	} 
	else 
	{
		aatype = D3DMULTISAMPLE_NONMASKABLE;
		aalevel = mode.antialiasLevel-1;
	}
  
	_validateMultisampleParams(fmt, aatype, aalevel);
   
	d3dpp.BackBufferWidth  = mode.resolution.x;
	d3dpp.BackBufferHeight = mode.resolution.y;
	d3dpp.BackBufferFormat = fmt;
	d3dpp.BackBufferCount  = 2;	// anis -> triple buffering to avoid tearing! NOTE: would be cool to set it from graphics options...
	d3dpp.MultiSampleType  = aatype;
	d3dpp.MultiSampleQuality = aalevel;
	d3dpp.SwapEffect       = /* IsWin7OrLater() ? D3DSWAPEFFECT_FLIPEX : */ D3DSWAPEFFECT_DISCARD; // NOTE: anis -> DirectX9Ex support for windows 7 or more current
	d3dpp.hDeviceWindow    = hwnd;
	d3dpp.Windowed         = !mode.fullScreen;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = GFXD3D9TextureFormat[GFXFormatD24S8];
	d3dpp.Flags            = 0;
	d3dpp.FullScreen_RefreshRateInHz = (mode.refreshRate == 0 || !mode.fullScreen) ?  D3DPRESENT_RATE_DEFAULT : mode.refreshRate;
	d3dpp.PresentationInterval = smDisableVSync ? D3DPRESENT_INTERVAL_IMMEDIATE : D3DPRESENT_INTERVAL_DEFAULT;

	return d3dpp;
}

void GFXD3D9Device::enumerateAdapters(Vector<GFXAdapter*> &adapterList)
{
	LPDIRECT3D9EX d3d9;
	HRESULT hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &d3d9);

	if(FAILED(hr))
	{
		Con::errorf("Unsupported DirectX version!");
		Platform::messageBox(Con::getVariable("$appName"), "DirectX could not be started!\r\nPlease be sure you have the latest version of DirectX installed.", MBOk, MIStop);
		Platform::forceShutdown(-1);
	}

	for(U32 adapterIndex = 0; adapterIndex < d3d9->GetAdapterCount(); adapterIndex++) 
	{
		GFXAdapter *toAdd = new GFXAdapter;
		toAdd->mType  = Direct3D9;
		toAdd->mIndex = adapterIndex;
		toAdd->mCreateDeviceInstanceDelegate = mCreateDeviceInstance;

		// Grab the shader model.
		D3DCAPS9 caps;
		d3d9->GetDeviceCaps(adapterIndex, D3DDEVTYPE_HAL, &caps);
		U8 *pxPtr = (U8*)&caps.PixelShaderVersion;
		toAdd->mShaderModel = pxPtr[1] + pxPtr[0] * 0.1;

		// Get the device description string.
		D3DADAPTER_IDENTIFIER9 temp;
		d3d9->GetAdapterIdentifier(adapterIndex, NULL, &temp); // The NULL is the flags which deal with WHQL

		dStrncpy(toAdd->mName, temp.Description, GFXAdapter::MaxAdapterNameLen);
		dStrncat(toAdd->mName, " (D3D9)", GFXAdapter::MaxAdapterNameLen);

		// And the output display device name
		dStrncpy(toAdd->mOutputName, temp.DeviceName, GFXAdapter::MaxAdapterNameLen);

		// Video mode enumeration.
		D3DFORMAT formats[] =	{		
									GFXD3D9TextureFormat[GFXFormatR5G6B5],		// 16bit format
									GFXD3D9TextureFormat[GFXFormatR8G8B8X8]		// 32bit format
								};

		for(S32 i = 0; i < ARRAYSIZE(formats); i++) 
		{
			DWORD MaxSampleQualities;
			d3d9->CheckDeviceMultiSampleType(adapterIndex, D3DDEVTYPE_HAL, formats[i], FALSE, D3DMULTISAMPLE_NONMASKABLE, &MaxSampleQualities);

			D3DDISPLAYMODEFILTER filter;
			filter.Format = formats[i];
			filter.ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;
			filter.Size = sizeof(filter);

			for(U32 j = 0; j < d3d9->GetAdapterModeCountEx(adapterIndex, &filter); j++) 
			{
				D3DDISPLAYMODEEX mode;
				ZeroMemory(&mode, sizeof(mode));
				mode.Size = sizeof(mode);

				HRESULT hres = d3d9->EnumAdapterModesEx(adapterIndex, &filter, j, &mode);

				if(FAILED(hres))
				{
					AssertFatal(false, "GFXD3D9Device::enumerateAdapters - EnumAdapterModesEx failed!");
				}

				GFXVideoMode vmAdd;
				vmAdd.bitDepth    = i == 0 ? 16 : 32;
				vmAdd.fullScreen  = true;
				vmAdd.refreshRate = mode.RefreshRate;
				vmAdd.resolution  = Point2I(mode.Width, mode.Height);
				vmAdd.antialiasLevel = MaxSampleQualities;
				toAdd->mAvailableModes.push_back(vmAdd);
			}
		}

		adapterList.push_back(toAdd);
	}

	d3d9->Release();
}

void GFXD3D9Device::enumerateVideoModes() 
{
	D3DFORMAT formats[] =	{		
								GFXD3D9TextureFormat[GFXFormatR5G6B5],		// 16bit format
								GFXD3D9TextureFormat[GFXFormatR8G8B8X8]		// 32bit format
							};

	for(S32 i = 0; i < ARRAYSIZE(formats); i++) 
	{
		D3DDISPLAYMODEFILTER filter;
		filter.Format = formats[i];
		filter.ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;
		filter.Size = sizeof(filter);

		for( U32 j = 0; j < mD3D->GetAdapterModeCountEx(mAdapterIndex, &filter); j++) 
		{
			D3DDISPLAYMODEEX mode;
			ZeroMemory(&mode, sizeof(mode));
			mode.Size = sizeof(mode);

			HRESULT hres = mD3D->EnumAdapterModesEx(mAdapterIndex, &filter, j, &mode);

			if(FAILED(hres))
			{
				AssertFatal(false, "GFXD3D9Device::enumerateVideoModes - EnumAdapterModesEx failed!");
			}

			GFXVideoMode toAdd;
			toAdd.bitDepth = i == 0 ? 16 : 32;
			toAdd.fullScreen = false;
			toAdd.refreshRate = mode.RefreshRate;
			toAdd.resolution = Point2I(mode.Width, mode.Height);

			mVideoModes.push_back(toAdd);
		}
	}
}

void GFXD3D9Device::init(const GFXVideoMode &mode, PlatformWindow *window)
{
	AssertFatal(window, "GFXD3D9Device::init - must specify a window!");

	Win32Window *win = static_cast<Win32Window*>(window);
	AssertISV(win, "GFXD3D9Device::init - got a non Win32Window window passed in! Did DX go crossplatform?");

	HWND winHwnd = win->getHWND();

	D3DPRESENT_PARAMETERS d3dpp = setupPresentParams(mode, winHwnd);
	mMultisampleType = d3dpp.MultiSampleType;
	mMultisampleLevel = d3dpp.MultiSampleQuality;

	D3DDISPLAYMODEEX FullscreenDisplayMode;
	FullscreenDisplayMode.Format = d3dpp.BackBufferFormat;
	FullscreenDisplayMode.Height = d3dpp.BackBufferHeight;
	FullscreenDisplayMode.Width = d3dpp.BackBufferWidth;
	FullscreenDisplayMode.RefreshRate = d3dpp.FullScreen_RefreshRateInHz;
	FullscreenDisplayMode.Size = sizeof(FullscreenDisplayMode);
	FullscreenDisplayMode.ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;

	HRESULT hres;
    U32 deviceFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE;

    // Try to do pure, unless we're doing debug (and thus doing more paranoid checking).
#ifndef TORQUE_DEBUG
    deviceFlags |= D3DCREATE_PUREDEVICE;
#endif

	hres = mD3D->CreateDeviceEx(mAdapterIndex, D3DDEVTYPE_HAL, winHwnd, deviceFlags, &d3dpp, d3dpp.Windowed ? NULL : &FullscreenDisplayMode, &mD3DDevice);

    if(FAILED(hres) && hres != D3DERR_OUTOFVIDEOMEMORY)
    {
		Con::errorf("Failed to create hardware device, trying mixed device");
		deviceFlags &= (~D3DCREATE_PUREDEVICE);
		deviceFlags &= (~D3DCREATE_HARDWARE_VERTEXPROCESSING);
		deviceFlags |= D3DCREATE_MIXED_VERTEXPROCESSING;

        hres = mD3D->CreateDeviceEx(mAdapterIndex, D3DDEVTYPE_HAL, winHwnd, deviceFlags, &d3dpp, d3dpp.Windowed ? NULL : &FullscreenDisplayMode, &mD3DDevice);

        if(FAILED(hres) && hres != D3DERR_OUTOFVIDEOMEMORY)
        {
			Con::errorf("Failed to create mixed mode device, trying software device");
			deviceFlags &= (~D3DCREATE_MIXED_VERTEXPROCESSING);
			deviceFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

			hres = mD3D->CreateDeviceEx(mAdapterIndex, D3DDEVTYPE_HAL, winHwnd, deviceFlags, &d3dpp, d3dpp.Windowed ? NULL : &FullscreenDisplayMode, &mD3DDevice);

			if (FAILED(hres) && hres != D3DERR_OUTOFVIDEOMEMORY)
			{
				Con::errorf("Failed to create software device, giving up");
			}

			if(FAILED(hres))
			{
				AssertFatal(false, "GFXD3D9Device::init - CreateDevice failed!");
			}
        }
    }

	if(!mD3DDevice)
	{
		if (hres == D3DERR_OUTOFVIDEOMEMORY)
		{
			char errorMsg[4096];
			dSprintf(errorMsg, sizeof(errorMsg), "Out of video memory. Close other windows, reboot, and/or upgrade your video card drivers. Your video card is: %s", getAdapter().getName());
			Platform::AlertOK("DirectX Error", errorMsg);
		}

		else
		{
			Platform::AlertOK("DirectX Error!", "Failed to initialize Direct3D! Make sure you have DirectX 9 installed, and are running a graphics card that supports Shader Model 3.");
		}

		Platform::forceShutdown(1);
	}

	mTextureManager = new GFXD3D9TextureManager();

	// Now reacquire all the resources we trashed earlier
	reacquireDefaultPoolResources();
      
	D3DCAPS9 caps;
	mD3DDevice->GetDeviceCaps(&caps);

	U8 *pxPtr = (U8*) &caps.PixelShaderVersion;

	mPixVersion = pxPtr[1] + pxPtr[0] * 0.1;
	if (mPixVersion >= 2.0f && mPixVersion < 3.0f && caps.PS20Caps.NumTemps >= 32)
		mPixVersion += 0.2f;
	else if (mPixVersion >= 2.0f && mPixVersion < 3.0f && caps.PS20Caps.NumTemps >= 22)
		mPixVersion += 0.1f;

	if(mPixVersion < 3.0f)
	{
		Platform::AlertOK("DirectX Error!", "Failed to initialize Direct3D! Make sure you have DirectX 9 installed, and are running a graphics card that supports Shader Model 3.");
		Platform::forceShutdown(1);
	}

	// detect max number of simultaneous render targets
	mNumRenderTargets = caps.NumSimultaneousRTs;
	Con::printf("Number of simultaneous render targets: %d", mNumRenderTargets);
   
	// detect occlusion query support
	if(SUCCEEDED(mD3DDevice->CreateQuery(D3DQUERYTYPE_OCCLUSION, NULL))) mOcclusionQuerySupported = true;

	Con::printf("Hardware occlusion query detected: %s", mOcclusionQuerySupported ? "Yes" : "No");
   
	mCardProfiler = new GFXD3D9CardProfiler(mAdapterIndex);
	mCardProfiler->init();

	gScreenShot = new GFXD3D9ScreenShot;

	mVideoFrameGrabber = new GFXD3D9VideoFrameGrabber();
	VIDCAP->setFrameGrabber(mVideoFrameGrabber);

	SAFE_RELEASE(mDeviceDepthStencil);
	HRESULT hr = mD3DDevice->GetDepthStencilSurface(&mDeviceDepthStencil);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D9Device::init - couldn't grab reference to device's depth-stencil surface.");
	}

	mInitialized = true;
	deviceInited();
}

void GFXD3D9Device::_validateMultisampleParams(D3DFORMAT format, D3DMULTISAMPLE_TYPE & aatype, DWORD & aalevel) const
{
   if(aatype != D3DMULTISAMPLE_NONE)
   {
      DWORD MaxSampleQualities;      
      mD3D->CheckDeviceMultiSampleType(mAdapterIndex, D3DDEVTYPE_HAL, format, FALSE, D3DMULTISAMPLE_NONMASKABLE, &MaxSampleQualities);
      aatype = D3DMULTISAMPLE_NONMASKABLE;
      aalevel = getMin((U32)aalevel, (U32)MaxSampleQualities-1);
   }
}

bool GFXD3D9Device::beginSceneInternal() 
{
   HRESULT hr = mD3DDevice->BeginScene();

   if(FAILED(hr)) 
   {
       AssertFatal(false, "GFXD3D9Device::beginSceneInternal - failed to BeginScene");
   }

   mCanCurrentlyRender = SUCCEEDED(hr);
   return mCanCurrentlyRender;   
}

GFXWindowTarget * GFXD3D9Device::allocWindowTarget(PlatformWindow *window)
{
	AssertFatal(window,"GFXD3D9Device::allocWindowTarget - no window provided!");

	// Set up a new window target...
	GFXD3D9WindowTarget *gdwt = new GFXD3D9WindowTarget();
	gdwt->mWindow = window;
	gdwt->mSize = window->getClientExtent();
	gdwt->initPresentationParams();

	// Allocate the device.
	init(window->getVideoMode(), window);

	SAFE_RELEASE(mDeviceDepthStencil);   
	mD3DDevice->GetDepthStencilSurface(&mDeviceDepthStencil);
	SAFE_RELEASE(mDeviceBackbuffer);
	mD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &mDeviceBackbuffer);

	gdwt->registerResourceWithDevice(this);
	return gdwt;
}

GFXTextureTarget* GFXD3D9Device::allocRenderToTextureTarget()
{
   GFXD3D9TextureTarget *targ = new GFXD3D9TextureTarget();
   targ->registerResourceWithDevice(this);

   return targ;
}

void GFXD3D9Device::reset(D3DPRESENT_PARAMETERS &d3dpp)
{
	if(!mD3DDevice)
		return;

	mInitialized = false;

	mMultisampleType = d3dpp.MultiSampleType;
	mMultisampleLevel = d3dpp.MultiSampleQuality;
	_validateMultisampleParams(d3dpp.BackBufferFormat, mMultisampleType, mMultisampleLevel);

	// Clean up some commonly dangling state. This helps prevents issues with
	// items that are destroyed by the texture manager callbacks and recreated
	// later, but still left bound.
	setVertexBuffer(NULL);
	setPrimitiveBuffer(NULL);

	for(S32 i = 0; i < getNumSamplers(); i++)
		setTexture(i, NULL);

	// First release all the stuff we allocated from D3DPOOL_DEFAULT
	releaseDefaultPoolResources();

	// reset device
	Con::printf("--- Resetting D3D9 Device ---");

	D3DDISPLAYMODEEX FullscreenDisplayMode;
	FullscreenDisplayMode.Format = d3dpp.BackBufferFormat;
	FullscreenDisplayMode.Height = d3dpp.BackBufferHeight;
	FullscreenDisplayMode.Width = d3dpp.BackBufferWidth;
	FullscreenDisplayMode.RefreshRate = d3dpp.FullScreen_RefreshRateInHz;
	FullscreenDisplayMode.Size = sizeof(FullscreenDisplayMode);
	FullscreenDisplayMode.ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;

	HRESULT hres = mD3DDevice->ResetEx(&d3dpp, d3dpp.Windowed ? NULL : &FullscreenDisplayMode);

	if(FAILED(hres))
	{
		AssertFatal(false, "GFXD3D9Device::reset - Reset call failure");
	}

	mInitialized = true;

	// Now re aquire all the resources we trashed earlier
	reacquireDefaultPoolResources();

	// Mark everything dirty and flush to card, for sanity.
	updateStates(true);
}

//
// Register this device with GFXInit
//
class GFXPCD3D9RegisterDevice
{
public:
   GFXPCD3D9RegisterDevice()
   {
      GFXInit::getRegisterDeviceSignal().notify(&GFXD3D9Device::enumerateAdapters);
   }
};

static GFXPCD3D9RegisterDevice pPCD3D9RegisterDevice;

//-----------------------------------------------------------------------------
/// Parse command line arguments for window creation
//-----------------------------------------------------------------------------
static void sgPCD3D9DeviceHandleCommandLine(S32 argc, const char **argv)
{
   // anis -> useful to pass parameters by command line for d3d (e.g. -dx9 -dx11)
   for (U32 i = 1; i < argc; i++)
   {
      argv[i];
   }   
}

// Register the command line parsing hook
static ProcessRegisterCommandLine sgCommandLine( sgPCD3D9DeviceHandleCommandLine );

GFXD3D9Device::GFXD3D9Device(LPDIRECT3D9EX d3d, U32 index) : mVideoFrameGrabber( NULL ) 
{
   mDeviceSwizzle32 = &Swizzles::bgra;
   GFXVertexColor::setSwizzle( mDeviceSwizzle32 );

   mDeviceSwizzle24 = &Swizzles::bgr;

   mD3D = d3d;
   mAdapterIndex = index;
   mD3DDevice = NULL;
   mVolatileVB = NULL;

   mCurrentPB = NULL;
   mDynamicPB = NULL;

   mLastVertShader = NULL;
   mLastPixShader = NULL;

   mCanCurrentlyRender = false;
   mTextureManager = NULL;
   mCurrentStateBlock = NULL;

   mPixVersion = 0.0;
   mNumRenderTargets = 0;

   mCardProfiler = NULL;

   mDeviceDepthStencil = NULL;
   mDeviceBackbuffer = NULL;
   mDeviceColor = NULL;

   mCreateFenceType = -1; // Unknown, test on first allocate

   mCurrentConstBuffer = NULL;

   mOcclusionQuerySupported = false;

   for(int i = 0; i < GS_COUNT; ++i)
      mModelViewProjSC[i] = NULL;

   // Set up the Enum translation tables
   GFXD3D9EnumTranslate::init();
}

GFXD3D9Device::~GFXD3D9Device() 
{
   if(mVideoFrameGrabber)
   {
      if(ManagedSingleton< VideoCapture >::instanceOrNull())
		VIDCAP->setFrameGrabber(NULL);

      delete mVideoFrameGrabber;
   }

   // Release our refcount on the current stateblock object
   mCurrentStateBlock = NULL;
   releaseDefaultPoolResources();

   // Free the vertex declarations.
   VertexDeclMap::Iterator iter = mVertexDecls.begin();
   for(;iter != mVertexDecls.end(); iter++)
      delete iter->value;

   // Forcibly clean up the pools
   mVolatileVBList.setSize(0);
   mDynamicPB = NULL;

   // And release our D3D resources.
   SAFE_RELEASE(mDeviceDepthStencil);
   SAFE_RELEASE(mDeviceBackbuffer)
   SAFE_RELEASE(mDeviceColor);
   SAFE_RELEASE(mD3DDevice);
   SAFE_RELEASE(mD3D);

   if(mCardProfiler)
   {
      delete mCardProfiler;
      mCardProfiler = NULL;
   }

   if(gScreenShot)
   {
      delete gScreenShot;
      gScreenShot = NULL;
   }
}

/*
	GFXD3D9Device::setupGenericShaders

	Anis -> used just for draw some ui elements, this implementation avoid to use fixed pipeline functions.
*/

void GFXD3D9Device::setupGenericShaders(GenericShaderType type)
{
   AssertFatal(type != GSTargetRestore, ""); //not used

   if(mGenericShader[GSColor] == NULL)
   {
	  ShaderData *shaderData;

      shaderData = new ShaderData();
      shaderData->setField("DXVertexShaderFile", "shaders/common/fixedFunction/colorV.hlsl");
      shaderData->setField("DXPixelShaderFile", "shaders/common/fixedFunction/colorP.hlsl");
      shaderData->setField("pixVersion", "2.0");
      shaderData->registerObject();
      mGenericShader[GSColor] =  shaderData->getShader();
      mGenericShaderBuffer[GSColor] = mGenericShader[GSColor]->allocConstBuffer();
      mModelViewProjSC[GSColor] = mGenericShader[GSColor]->getShaderConstHandle("$modelView");

      shaderData = new ShaderData();
      shaderData->setField("DXVertexShaderFile", "shaders/common/fixedFunction/modColorTextureV.hlsl");
      shaderData->setField("DXPixelShaderFile", "shaders/common/fixedFunction/modColorTextureP.hlsl");
      shaderData->setField("pixVersion", "2.0");
      shaderData->registerObject();
      mGenericShader[GSModColorTexture] = shaderData->getShader();
      mGenericShaderBuffer[GSModColorTexture] = mGenericShader[GSModColorTexture]->allocConstBuffer();
      mModelViewProjSC[GSModColorTexture] = mGenericShader[GSModColorTexture]->getShaderConstHandle("$modelView");

      shaderData = new ShaderData();
      shaderData->setField("DXVertexShaderFile", "shaders/common/fixedFunction/addColorTextureV.hlsl");
      shaderData->setField("DXPixelShaderFile", "shaders/common/fixedFunction/addColorTextureP.hlsl");
      shaderData->setField("pixVersion", "2.0");
      shaderData->registerObject();
      mGenericShader[GSAddColorTexture] = shaderData->getShader();
      mGenericShaderBuffer[GSAddColorTexture] = mGenericShader[GSAddColorTexture]->allocConstBuffer();
      mModelViewProjSC[GSAddColorTexture] = mGenericShader[GSAddColorTexture]->getShaderConstHandle("$modelView");

      shaderData = new ShaderData();
      shaderData->setField("DXVertexShaderFile", "shaders/common/fixedFunction/textureV.hlsl");
      shaderData->setField("DXPixelShaderFile", "shaders/common/fixedFunction/textureP.hlsl");
      shaderData->setField("pixVersion", "2.0");
      shaderData->registerObject();
      mGenericShader[GSTexture] = shaderData->getShader();
      mGenericShaderBuffer[GSTexture] = mGenericShader[GSTexture]->allocConstBuffer();
      mModelViewProjSC[GSTexture] = mGenericShader[GSTexture]->getShaderConstHandle("$modelView");
   }

   MatrixF tempMatrix =  mProjectionMatrix * mViewMatrix * mWorldMatrix[mWorldStackSize];  
   mGenericShaderBuffer[type]->setSafe(mModelViewProjSC[type], tempMatrix);

   setShader(mGenericShader[type]);
   setShaderConstBuffer(mGenericShaderBuffer[type]);
}

//-----------------------------------------------------------------------------
/// Creates a state block object based on the desc passed in.  This object
/// represents an immutable state.
GFXStateBlockRef GFXD3D9Device::createStateBlockInternal(const GFXStateBlockDesc& desc)
{
   return GFXStateBlockRef(new GFXD3D9StateBlock(desc));
}

/// Activates a stateblock
void GFXD3D9Device::setStateBlockInternal(GFXStateBlock* block, bool force)
{
   AssertFatal(static_cast<GFXD3D9StateBlock*>(block), "Incorrect stateblock type for this device!");
   GFXD3D9StateBlock* d3dBlock = static_cast<GFXD3D9StateBlock*>(block);
   GFXD3D9StateBlock* d3dCurrent = static_cast<GFXD3D9StateBlock*>(mCurrentStateBlock.getPointer());
   if (force)
      d3dCurrent = NULL;
   d3dBlock->activate(d3dCurrent);   
}

/// Called by base GFXDevice to actually set a const buffer
void GFXD3D9Device::setShaderConstBufferInternal(GFXShaderConstBuffer* buffer)
{
   if(buffer)
   {
      PROFILE_SCOPE(GFXD3D9Device_setShaderConstBufferInternal);
      AssertFatal(static_cast<GFXD3D9ShaderConstBuffer*>(buffer), "Incorrect shader const buffer type for this device!");
      GFXD3D9ShaderConstBuffer* d3dBuffer = static_cast<GFXD3D9ShaderConstBuffer*>(buffer);

      d3dBuffer->activate(mCurrentConstBuffer);
      mCurrentConstBuffer = d3dBuffer;
   }
   
   else
   {
      mCurrentConstBuffer = NULL;
   }
}

//-----------------------------------------------------------------------------

void GFXD3D9Device::clear(U32 flags, ColorI color, F32 z, U32 stencil) 
{
   // Make sure we have flushed our render target state.
   _updateRenderTargets();

   // Kind of a bummer we have to do this, there should be a better way made
   DWORD realflags = 0;

   if(flags & GFXClearTarget)
      realflags |= D3DCLEAR_TARGET;

   if(flags & GFXClearZBuffer)
      realflags |= D3DCLEAR_ZBUFFER;

   if(flags & GFXClearStencil)
      realflags |= D3DCLEAR_STENCIL;

   mD3DDevice->Clear(0, NULL, realflags, D3DCOLOR_ARGB(color.alpha, color.red, color.green, color.blue), z, stencil);
}

void GFXD3D9Device::endSceneInternal() 
{
   mD3DDevice->EndScene();
   mCanCurrentlyRender = false;
}

void GFXD3D9Device::_updateRenderTargets()
{
   if (mRTDirty || (mCurrentRT && mCurrentRT->isPendingState()))
   {
      if (mRTDeactivate)
      {
         mRTDeactivate->deactivate();
         mRTDeactivate = NULL;   
      }

      // NOTE: The render target changes are not really accurate
      // as the GFXTextureTarget supports MRT internally.  So when
      // we activate a GFXTarget it could result in multiple calls
      // to SetRenderTarget on the actual device.
      mDeviceStatistics.mRenderTargetChanges++;

      mCurrentRT->activate();

      mRTDirty = false;
   }  

   if (mViewportDirty)
   {
      D3DVIEWPORT9 viewport;
      viewport.X       = mViewport.point.x;
      viewport.Y       = mViewport.point.y;
      viewport.Width   = mViewport.extent.x;
      viewport.Height  = mViewport.extent.y;
      viewport.MinZ    = 0.0;
      viewport.MaxZ    = 1.0;

      HRESULT hr = mD3DDevice->SetViewport(&viewport);

	  if(FAILED(hr)) 
	  {
	  	  AssertFatal(false, "GFXD3D9Device::_updateRenderTargets() - Error setting viewport!");
	  }

	  mViewportDirty = false;
   }
}

void GFXD3D9Device::releaseDefaultPoolResources() 
{
   // Release all the dynamic vertex buffer arrays
   // Forcibly clean up the pools
   for(U32 i=0; i<mVolatileVBList.size(); i++)
   {
      mVolatileVBList[i]->vb->Release();
      mVolatileVBList[i]->vb = NULL;
      mVolatileVBList[i] = NULL;
   }
   mVolatileVBList.setSize(0);

   // We gotta clear the current const buffer else the next
   // activate may erroneously think the device is still holding
   // this state and fail to set it.   
   mCurrentConstBuffer = NULL;

   // Set current VB to NULL and set state dirty
   for (U32 i=0; i < VERTEX_STREAM_COUNT; i++)
   {
      mCurrentVertexBuffer[i] = NULL;
      mVertexBufferDirty[i] = true;
      mVertexBufferFrequency[i] = 0;
      mVertexBufferFrequencyDirty[i] = true;
   }

   // Release dynamic index buffer
   if(mDynamicPB != NULL)
   {
      SAFE_RELEASE(mDynamicPB->ib);
   }

   // Set current PB/IB to NULL and set state dirty
   mCurrentPrimitiveBuffer = NULL;
   mCurrentPB = NULL;
   mPrimitiveBufferDirty = true;

   // Zombify texture manager (for D3D this only modifies default pool textures)
   if( mTextureManager ) 
      mTextureManager->zombify();

   // Kill off other potentially dangling references...
   SAFE_RELEASE(mDeviceDepthStencil);
   SAFE_RELEASE(mDeviceBackbuffer);
   mD3DDevice->SetDepthStencilSurface(NULL);

   // Set global dirty state so the IB/PB and VB get reset
   mStateDirty = true;
}

void GFXD3D9Device::reacquireDefaultPoolResources() 
{
	// Now do the dynamic index buffers
	if(mDynamicPB == NULL)
		mDynamicPB = new GFXD3D9PrimitiveBuffer(this, 0, 0, GFXBufferTypeDynamic);

	HRESULT hr = mD3DDevice->CreateIndexBuffer(sizeof(U16) * MAX_DYNAMIC_INDICES, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &mDynamicPB->ib, NULL);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "Failed to allocate dynamic IB");
	}

	// Grab the depth-stencil...
	SAFE_RELEASE(mDeviceDepthStencil);   
	hr = mD3DDevice->GetDepthStencilSurface(&mDeviceDepthStencil);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D9Device::reacquireDefaultPoolResources - couldn't grab reference to device's depth-stencil surface.");
	}

	SAFE_RELEASE(mDeviceBackbuffer);
	mD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &mDeviceBackbuffer);

	// Store for query later.
	mD3DDevice->GetDisplayModeEx(0, &mDisplayMode, &mDisplayRotation);

	if(mTextureManager)
		mTextureManager->resurrect();
}

GFXD3D9VertexBuffer* GFXD3D9Device::findVBPool( const GFXVertexFormat *vertexFormat, U32 vertsNeeded )
{
	PROFILE_SCOPE(GFXD3D9Device_findVBPool);

	for(U32 i=0; i<mVolatileVBList.size(); i++)
		if(mVolatileVBList[i]->mVertexFormat.isEqual(*vertexFormat))
			return mVolatileVBList[i];

	return NULL;
}

GFXD3D9VertexBuffer * GFXD3D9Device::createVBPool( const GFXVertexFormat *vertexFormat, U32 vertSize )
{
   PROFILE_SCOPE(GFXD3D9Device_createVBPool);

   // this is a bit funky, but it will avoid problems with (lack of) copy constructors
   //    with a push_back() situation
   mVolatileVBList.increment();
   StrongRefPtr<GFXD3D9VertexBuffer> newBuff;
   mVolatileVBList.last() = new GFXD3D9VertexBuffer();
   newBuff = mVolatileVBList.last();

   newBuff->mNumVerts   = 0;
   newBuff->mBufferType = GFXBufferTypeVolatile;
   newBuff->mVertexFormat.copy( *vertexFormat );
   newBuff->mVertexSize = vertSize;
   newBuff->mDevice = this;

   // Requesting it will allocate it.
   vertexFormat->getDecl();

   HRESULT hr = mD3DDevice->CreateVertexBuffer(	vertSize * MAX_DYNAMIC_VERTS, 
												D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,
												0, 
												D3DPOOL_DEFAULT, 
												&newBuff->vb, 
												NULL );

   if(FAILED(hr)) 
   {
       AssertFatal(false, "Failed to allocate dynamic VB");
   }

   return newBuff;
}

//-----------------------------------------------------------------------------

void GFXD3D9Device::setClipRect(const RectI &inRect) 
{
   // We transform the incoming rect by the view 
   // matrix first, so that it can be used to pan
   // and scale the clip rect.
   //
   // This is currently used to take tiled screenshots.
   Point3F pos(inRect.point.x, inRect.point.y, 0.0f);
   Point3F extent(inRect.extent.x, inRect.extent.y, 0.0f);
   getViewMatrix().mulP(pos);
   getViewMatrix().mulV(extent);  
   RectI rect(pos.x, pos.y, extent.x, extent.y);

   // Clip the rect against the renderable size.
   Point2I size = mCurrentRT->getSize();

   RectI maxRect(Point2I(0,0), size);
   rect.intersect(maxRect);

   mClipRect = rect;

   F32 l = F32( mClipRect.point.x);
   F32 r = F32( mClipRect.point.x + mClipRect.extent.x);
   F32 b = F32( mClipRect.point.y + mClipRect.extent.y);
   F32 t = F32( mClipRect.point.y);

   // Set up projection matrix, 
   static Point4F pt;   
   pt.set(2.0f / (r - l), 0.0f, 0.0f, 0.0f);
   mTempMatrix.setColumn(0, pt);

   pt.set(0.0f, 2.0f/(t - b), 0.0f, 0.0f);
   mTempMatrix.setColumn(1, pt);

   pt.set(0.0f, 0.0f, 1.0f, 0.0f);
   mTempMatrix.setColumn(2, pt);

   pt.set((l+r)/(l-r), (t+b)/(b-t), 1.0f, 1.0f);
   mTempMatrix.setColumn(3, pt);

   setProjectionMatrix(mTempMatrix);

   // Set up world/view matrix
   mTempMatrix.identity();   
   setWorldMatrix(mTempMatrix);

   setViewport(mClipRect);
}

void GFXD3D9Device::setVertexStream(U32 stream, GFXVertexBuffer *buffer)
{
   GFXD3D9VertexBuffer *d3dBuffer = static_cast<GFXD3D9VertexBuffer*>(buffer);

   if(stream == 0)
   {
      // Set the volatile buffer which is used to 
      // offset the start index when doing draw calls.
      if(d3dBuffer && d3dBuffer->mVolatileStart > 0)
         mVolatileVB = d3dBuffer;
      else
         mVolatileVB = NULL;
   }

   // NOTE: We do not use the stream offset here for stream 0
   // as that feature is *supposedly* not as well supported as 
   // using the start index in drawPrimitive.
   //
   // If we can verify that this is not the case then we should
   // start using this method exclusively for all streams.
   
   HRESULT hr = mD3DDevice->SetStreamSource( stream, 
                                             d3dBuffer ? d3dBuffer->vb : NULL,
                                             d3dBuffer && stream != 0 ? d3dBuffer->mVolatileStart * d3dBuffer->mVertexSize : 0, 
                                             d3dBuffer ? d3dBuffer->mVertexSize : 0 );
   if(FAILED(hr)) 
   {
       AssertFatal(false, "GFXD3D9Device::setVertexStream - Failed to set stream source.");
   }
}

void GFXD3D9Device::setVertexStreamFrequency(U32 stream, U32 frequency)
{
   if(frequency == 0)
      frequency = 1;
   else
   {
      if(stream == 0)
         frequency = D3DSTREAMSOURCE_INDEXEDDATA | frequency;
      else
         frequency = D3DSTREAMSOURCE_INSTANCEDATA | frequency;
   }

   HRESULT hr = mD3DDevice->SetStreamSourceFreq(stream, frequency);

   if(FAILED(hr)) 
   {
       AssertFatal(false, "GFXD3D9Device::setVertexStreamFrequency - Failed to set stream frequency.");
   }
}

void GFXD3D9Device::_setPrimitiveBuffer(GFXPrimitiveBuffer *buffer) 
{
   mCurrentPB = static_cast<GFXD3D9PrimitiveBuffer *>(buffer);

   HRESULT hr = mD3DDevice->SetIndices(mCurrentPB->ib);

   if(FAILED(hr)) 
   {
       AssertFatal(false, "Failed to set indices");
   }
}

void GFXD3D9Device::drawPrimitive(GFXPrimitiveType primType, U32 vertexStart, U32 primitiveCount) 
{
   // This is done to avoid the function call overhead if possible
   if(mStateDirty)
      updateStates();
   if(mCurrentShaderConstBuffer)
      setShaderConstBufferInternal(mCurrentShaderConstBuffer);

   if(mVolatileVB)
      vertexStart += mVolatileVB->mVolatileStart;

   HRESULT hr = mD3DDevice->DrawPrimitive(GFXD3D9PrimType[primType], vertexStart, primitiveCount);

   if(FAILED(hr)) 
   {
       AssertFatal(false, "Failed to draw primitives");
   }

   mDeviceStatistics.mDrawCalls++;
   if(mVertexBufferFrequency[0] > 1)
      mDeviceStatistics.mPolyCount += primitiveCount * mVertexBufferFrequency[0];
   else
      mDeviceStatistics.mPolyCount += primitiveCount;
}

void GFXD3D9Device::drawIndexedPrimitive( GFXPrimitiveType primType, 
                                          U32 startVertex, 
                                          U32 minIndex, 
                                          U32 numVerts, 
                                          U32 startIndex, 
                                          U32 primitiveCount ) 
{
   // This is done to avoid the function call overhead if possible
   if(mStateDirty)
      updateStates();
   if (mCurrentShaderConstBuffer)
      setShaderConstBufferInternal(mCurrentShaderConstBuffer);

   AssertFatal(mCurrentPB != NULL, "Trying to call drawIndexedPrimitive with no current index buffer, call setIndexBuffer()");

   if(mVolatileVB)
      startVertex += mVolatileVB->mVolatileStart;

   HRESULT hr = mD3DDevice->DrawIndexedPrimitive(GFXD3D9PrimType[primType], startVertex, minIndex, numVerts, mCurrentPB->mVolatileStart + startIndex, primitiveCount);

   if(FAILED(hr)) 
   {
       AssertFatal(false, "Failed to draw indexed primitive");
   }

   mDeviceStatistics.mDrawCalls++;
   if(mVertexBufferFrequency[0] > 1)
      mDeviceStatistics.mPolyCount += primitiveCount * mVertexBufferFrequency[0];
   else
      mDeviceStatistics.mPolyCount += primitiveCount;
}

GFXShader* GFXD3D9Device::createShader()
{
   GFXD3D9Shader* shader = new GFXD3D9Shader();
   shader->registerResourceWithDevice( this );
   return shader;
}

//-----------------------------------------------------------------------------
// Set shader - this function exists to make sure this is done in one place,
//              and to make sure redundant shader states are not being
//              sent to the card.
//-----------------------------------------------------------------------------
void GFXD3D9Device::setShader(GFXShader *shader)
{
   if(shader)
   {
	   GFXD3D9Shader *d3dShader = static_cast<GFXD3D9Shader*>(shader);

	   if( d3dShader->mPixShader != mLastPixShader )
	   {
		  mD3DDevice->SetPixelShader( d3dShader->mPixShader );
		  mLastPixShader = d3dShader->mPixShader;
	   }

	   if( d3dShader->mVertShader != mLastVertShader )
	   {
		  mD3DDevice->SetVertexShader( d3dShader->mVertShader );
		  mLastVertShader = d3dShader->mVertShader;
	   }
   }

   else
   {
	   setupGenericShaders();
   }
}

GFXPrimitiveBuffer * GFXD3D9Device::allocPrimitiveBuffer(U32 numIndices, U32 numPrimitives, GFXBufferType bufferType )
{
   // Allocate a buffer to return
   GFXD3D9PrimitiveBuffer * res = new GFXD3D9PrimitiveBuffer(this, numIndices, numPrimitives, bufferType);

   // Determine usage flags
   U32 usage = 0;
   D3DPOOL pool = D3DPOOL_DEFAULT;

   // Assumptions:
   //    - static buffers are write once, use many
   //    - dynamic buffers are write many, use many
   //    - volatile buffers are write once, use once
   // You may never read from a buffer.
   switch(bufferType)
   {
	   case GFXBufferTypeDynamic:
	   case GFXBufferTypeVolatile:
		  usage |= D3DUSAGE_DYNAMIC;
		  break;
   }

   // Register resource
   res->registerResourceWithDevice(this);

   // We never allow reading from a primitive buffer.
   usage |= D3DUSAGE_WRITEONLY;

   // Create d3d index buffer
   if(bufferType == GFXBufferTypeVolatile)
   {
        // Get it from the pool if it's a volatile...
        AssertFatal(numIndices < MAX_DYNAMIC_INDICES, "Cannot allocate that many indices in a volatile buffer, increase MAX_DYNAMIC_INDICES.");

        res->ib = mDynamicPB->ib;
        res->mVolatileBuffer = mDynamicPB;
   }
   else
   {
		// Otherwise, get it as a seperate buffer...
		HRESULT hr = mD3DDevice->CreateIndexBuffer(sizeof(U16) * numIndices, usage, D3DFMT_INDEX16, pool, &res->ib, 0);

		if(FAILED(hr)) 
		{
			AssertFatal(false, "Failed to allocate an index buffer.");
		}
   }

   return res;
}

GFXVertexBuffer * GFXD3D9Device::allocVertexBuffer(U32 numVerts, const GFXVertexFormat *vertexFormat, U32 vertSize, GFXBufferType bufferType)
{
   PROFILE_SCOPE( GFXD3D9Device_allocVertexBuffer );

   GFXD3D9VertexBuffer *res = new GFXD3D9VertexBuffer(   this, 
                                                         numVerts, 
                                                         vertexFormat, 
                                                         vertSize, 
                                                         bufferType );

   U32 usage = 0;
   D3DPOOL pool = D3DPOOL_DEFAULT;

   res->mNumVerts = 0;

   // Assumptions:
   //    - static buffers are write once, use many
   //    - dynamic buffers are write many, use many
   //    - volatile buffers are write once, use once
   // You may never read from a buffer.

   switch(bufferType)
   {
	   case GFXBufferTypeDynamic:
	   case GFXBufferTypeVolatile:
		  usage |= D3DUSAGE_DYNAMIC;
		  break;
   }

   // Register resource
   res->registerResourceWithDevice(this);

   // We never allow reading from a vertex buffer.
   usage |= D3DUSAGE_WRITEONLY;

   // Create vertex buffer
   if(bufferType == GFXBufferTypeVolatile)
   {
        // NOTE: Volatile VBs are pooled and will be allocated at lock time.
        AssertFatal(numVerts <= MAX_DYNAMIC_VERTS, "GFXD3D9Device::allocVertexBuffer - Volatile vertex buffer is too big... see MAX_DYNAMIC_VERTS!");
   }
   else
   {
		// Requesting it will allocate it.
		vertexFormat->getDecl();

		// Get a new buffer...
		HRESULT hr = mD3DDevice->CreateVertexBuffer(vertSize * numVerts, usage, 0, pool, &res->vb, NULL);

		if(FAILED(hr)) 
		{
			AssertFatal(false, "Failed to allocate VB");
		}
   }

   res->mNumVerts = numVerts;
   return res;
}

GFXVertexDecl* GFXD3D9Device::allocVertexDecl( const GFXVertexFormat *vertexFormat )
{
   PROFILE_SCOPE( GFXD3D9Device_allocVertexDecl );

   // First check the map... you shouldn't allocate VBs very often
   // if you want performance.  The map lookup should never become
   // a performance bottleneck.
   D3D9VertexDecl *decl = mVertexDecls[vertexFormat->getDescription()];
   if ( decl )
      return decl;

   // Setup the declaration struct.
   U32 elemCount = vertexFormat->getElementCount();
   U32 offsets[4] = { 0 };
   U32 stream;
   D3DVERTEXELEMENT9 *vd = new D3DVERTEXELEMENT9[ elemCount + 1 ];
   for ( U32 i=0; i < elemCount; i++ )
   {
      const GFXVertexElement &element = vertexFormat->getElement( i );
      
      stream = element.getStreamIndex();

      vd[i].Stream = stream;
      vd[i].Offset = offsets[stream];
      vd[i].Type = GFXD3D9DeclType[element.getType()];
      vd[i].Method = D3DDECLMETHOD_DEFAULT;

      // We force the usage index of 0 for everything but 
      // texture coords for now... this may change later.
      vd[i].UsageIndex = 0;

      if ( element.isSemantic( GFXSemantic::POSITION ) )
         vd[i].Usage = D3DDECLUSAGE_POSITION;
      else if ( element.isSemantic( GFXSemantic::NORMAL ) )
         vd[i].Usage = D3DDECLUSAGE_NORMAL;
      else if ( element.isSemantic( GFXSemantic::COLOR ) )
         vd[i].Usage = D3DDECLUSAGE_COLOR;
      else if ( element.isSemantic( GFXSemantic::TANGENT ) )
         vd[i].Usage = D3DDECLUSAGE_TANGENT;
      else if ( element.isSemantic( GFXSemantic::BINORMAL ) )
         vd[i].Usage = D3DDECLUSAGE_BINORMAL;
      else
      {
         // Anything that falls thru to here will be a texture coord.
         vd[i].Usage = D3DDECLUSAGE_TEXCOORD;
         vd[i].UsageIndex = element.getSemanticIndex();
      }

      offsets[stream] += element.getSizeInBytes();
   }

   D3DVERTEXELEMENT9 declEnd = D3DDECL_END();
   vd[elemCount] = declEnd;

   decl = new D3D9VertexDecl();
   HRESULT hr = mD3DDevice->CreateVertexDeclaration(vd, &decl->decl );

   if(FAILED(hr)) 
   {
       AssertFatal(false, "GFXD3D9Device::allocVertexDecl - Failed to create vertex declaration!");
   }

   delete [] vd;

   // Store it in the cache.
   mVertexDecls[vertexFormat->getDescription()] = decl;

   return decl;
}

void GFXD3D9Device::setVertexDecl( const GFXVertexDecl *decl )
{
   IDirect3DVertexDeclaration9 *dx9Decl = NULL;
   if ( decl )
      dx9Decl = static_cast<const D3D9VertexDecl*>( decl )->decl;
   HRESULT hr = mD3DDevice->SetVertexDeclaration( dx9Decl );

   if(FAILED(hr)) 
   {
       AssertFatal(false, "GFXD3D9Device::setVertexDecl - Failed to set vertex declaration.");
   }
}

//-----------------------------------------------------------------------------
// This function should ONLY be called from GFXDevice::updateStates() !!!
//-----------------------------------------------------------------------------
void GFXD3D9Device::setTextureInternal( U32 textureUnit, const GFXTextureObject *texture)
{
   if( texture == NULL )
   {
      HRESULT hr = mD3DDevice->SetTexture( textureUnit, NULL);
	  if(FAILED(hr)) 
	  {
		AssertFatal(false, "Failed to set texture to null!");
	  }
      return;
   }

	GFXD3D9TextureObject *tex = (GFXD3D9TextureObject *) texture;
	HRESULT hr = mD3DDevice->SetTexture( textureUnit, tex->getTex());

	if(FAILED(hr)) 
	{
		AssertFatal(false, "Failed to set texture to valid value!");
	}
}

GFXFence *GFXD3D9Device::createFence()
{
   // Figure out what fence type we should be making if we don't know
   if( mCreateFenceType == -1 )
   {
      IDirect3DQuery9 *testQuery = NULL;
      mCreateFenceType = ( mD3DDevice->CreateQuery( D3DQUERYTYPE_EVENT, &testQuery ) == D3DERR_NOTAVAILABLE );
      SAFE_RELEASE( testQuery );
   }

   // Cool, use queries
   if( !mCreateFenceType )
   {
      GFXFence* fence = new GFXD3D9QueryFence( this );
      fence->registerResourceWithDevice(this);
      return fence;
   }

   // CodeReview: At some point I would like a specialized D3D9 implementation of
   // the method used by the general fence, only without the overhead incurred 
   // by using the GFX constructs. Primarily the lock() method on texture handles
   // will do a data copy, and this method doesn't require a copy, just a lock
   // [5/10/2007 Pat]
   GFXFence* fence = new GFXGeneralFence( this );
   fence->registerResourceWithDevice(this);
   return fence;
}

GFXOcclusionQuery* GFXD3D9Device::createOcclusionQuery()
{  
   GFXOcclusionQuery *query;
   if (mOcclusionQuerySupported)
      query = new GFXD3D9OcclusionQuery( this );
   else
      return NULL;      

   query->registerResourceWithDevice(this);
   return query;
}

GFXCubemap * GFXD3D9Device::createCubemap()
{
   GFXD3D9Cubemap* cube = new GFXD3D9Cubemap();
   cube->registerResourceWithDevice(this);
   return cube;
}
