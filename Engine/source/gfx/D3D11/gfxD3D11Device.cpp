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
// D3D11 layer created by: Anis A. Hireche (C) 2014 - anishireche@gmail.com
//-----------------------------------------------------------------------------

#include "console/console.h"
#include "core/stream/fileStream.h"
#include "core/strings/unicode.h"
#include "core/util/journal/process.h"
#include "gfx/D3D11/gfxD3D11Device.h"
#include "gfx/D3D11/gfxD3D11CardProfiler.h"
#include "gfx/D3D11/gfxD3D11VertexBuffer.h"
#include "gfx/D3D11/gfxD3D11EnumTranslate.h"
#include "gfx/D3D11/gfxD3D11QueryFence.h"
#include "gfx/D3D11/gfxD3D11OcclusionQuery.h"
#include "gfx/D3D11/gfxD3D11Shader.h"
#include "gfx/D3D11/gfxD3D11Target.h"
#include "platformWin32/platformWin32.h"
#include "windowManager/win32/win32Window.h"
#include "windowManager/platformWindow.h"
#include "gfx/screenshot.h"
#include "materials/shaderData.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

/* 
	anis -> note:
	NVIDIA PerfHUD support has been removed because deprecated in favor of nvidia nsight which it doesn't require a special flag device for usage.
*/

GFXAdapter::CreateDeviceInstanceDelegate GFXD3D11Device::mCreateDeviceInstance(GFXD3D11Device::createInstance);

GFXDevice *GFXD3D11Device::createInstance(U32 adapterIndex)
{
   GFXD3D11Device* dev = new GFXD3D11Device(adapterIndex);
   return dev;
}

GFXFormat GFXD3D11Device::selectSupportedFormat(GFXTextureProfile *profile, const Vector<GFXFormat> &formats, bool texture, bool mustblend, bool mustfilter)
{
   for(U32 i = 0; i < formats.size(); i++)
   {
       if(GFXD3D11TextureFormat[formats[i]] == DXGI_FORMAT_UNKNOWN)
           continue;

       return formats[i];
   }
   
   return GFXFormatR8G8B8A8;
}

DXGI_SWAP_CHAIN_DESC GFXD3D11Device::setupPresentParams(const GFXVideoMode &mode, const HWND &hwnd) const
{
   DXGI_SWAP_CHAIN_DESC d3dpp;
   ZeroMemory(&d3dpp, sizeof(d3dpp));

   DXGI_SAMPLE_DESC sampleDesc;
   sampleDesc.Count = 1;
   sampleDesc.Quality = 0;

   d3dpp.BufferCount = !smDisableVSync ? 2 : 1;
   d3dpp.BufferDesc.Width = mode.resolution.x;
   d3dpp.BufferDesc.Height = mode.resolution.y;
   d3dpp.BufferDesc.Format = GFXD3D11TextureFormat[GFXFormatR8G8B8A8];
   d3dpp.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
   d3dpp.OutputWindow = hwnd;
   d3dpp.SampleDesc = sampleDesc;
   d3dpp.Windowed = !mode.fullScreen;
   d3dpp.BufferDesc.RefreshRate.Numerator = mode.refreshRate;
   d3dpp.BufferDesc.RefreshRate.Denominator = 1;
   d3dpp.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
   d3dpp.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
   d3dpp.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

   if(mode.fullScreen)
       d3dpp.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

   return d3dpp;
}

void GFXD3D11Device::enumerateAdapters(Vector<GFXAdapter*> &adapterList)
{
   IDXGIAdapter* EnumAdapter;
   IDXGIFactory* DXGIFactory;

   CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&DXGIFactory));

   for(U32 adapterIndex = 0; DXGIFactory->EnumAdapters(adapterIndex, &EnumAdapter) != DXGI_ERROR_NOT_FOUND; ++adapterIndex) 
   {
		GFXAdapter *toAdd = new GFXAdapter;
		toAdd->mType  = Direct3D11;
		toAdd->mIndex = adapterIndex;
		toAdd->mCreateDeviceInstanceDelegate = mCreateDeviceInstance;

		toAdd->mShaderModel = 5.0f;
		DXGI_ADAPTER_DESC desc;
		EnumAdapter->GetDesc(&desc);

		size_t size=wcslen(desc.Description);
		char * str=new char[size+1];

		wcstombs(str, desc.Description,size);
		str[size]='\0';
		String Description=str;
		delete str;

		dStrncpy(toAdd->mName, Description.c_str(), GFXAdapter::MaxAdapterNameLen);
		dStrncat(toAdd->mName, " (D3D11)", GFXAdapter::MaxAdapterNameLen);

		IDXGIOutput* pOutput = NULL; 
		HRESULT hr;

		hr = EnumAdapter->EnumOutputs(adapterIndex, &pOutput);

		if(hr == DXGI_ERROR_NOT_FOUND)
		{
			EnumAdapter->Release();
			break;
		}

		if(FAILED(hr))
			AssertFatal(false, "GFXD3D11Device::enumerateAdapters -> EnumOutputs call failure");

		UINT numModes = 0;
		DXGI_MODE_DESC* displayModes = NULL;
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// Get the number of elements
		hr = pOutput->GetDisplayModeList(format, 0, &numModes, NULL);

		if(FAILED(hr))
			AssertFatal(false, "GFXD3D11Device::enumerateAdapters -> GetDisplayModeList call failure");

		displayModes = new DXGI_MODE_DESC[numModes]; 

		// Get the list
		hr = pOutput->GetDisplayModeList(format, 0, &numModes, displayModes);

		if(FAILED(hr))
			AssertFatal(false, "GFXD3D11Device::enumerateAdapters -> GetDisplayModeList call failure");

		for(U32 numMode = 0; numMode < numModes; ++numMode)
		{
			GFXVideoMode vmAdd;

			vmAdd.fullScreen = true;
			vmAdd.refreshRate = displayModes[numMode].RefreshRate.Numerator / displayModes[numMode].RefreshRate.Denominator;
			vmAdd.resolution.x = displayModes[numMode].Width;
			vmAdd.resolution.y = displayModes[numMode].Height;
			toAdd->mAvailableModes.push_back(vmAdd);
		}

		delete displayModes;
		pOutput->Release();
		EnumAdapter->Release();
	    adapterList.push_back(toAdd);
   }

   DXGIFactory->Release();
}

void GFXD3D11Device::enumerateVideoModes() 
{
   mVideoModes.clear();

   IDXGIAdapter* EnumAdapter;
   IDXGIFactory* DXGIFactory;

   CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&DXGIFactory));

   for(U32 adapterIndex = 0; DXGIFactory->EnumAdapters(adapterIndex, &EnumAdapter) != DXGI_ERROR_NOT_FOUND; ++adapterIndex) 
   {
		IDXGIOutput* pOutput = NULL; 
		HRESULT hr;

		hr = EnumAdapter->EnumOutputs(adapterIndex, &pOutput);

		if(hr == DXGI_ERROR_NOT_FOUND)
		{
			EnumAdapter->Release();
			break;
		}

		if(FAILED(hr))
			AssertFatal(false, "GFXD3D11Device::enumerateVideoModes -> EnumOutputs call failure");

		UINT numModes = 0;
		DXGI_MODE_DESC* displayModes = NULL;
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// Get the number of elements
		hr = pOutput->GetDisplayModeList(format, 0, &numModes, NULL);

		if(FAILED(hr))
			AssertFatal(false, "GFXD3D11Device::enumerateVideoModes -> GetDisplayModeList call failure");

		displayModes = new DXGI_MODE_DESC[numModes]; 

		// Get the list
		hr = pOutput->GetDisplayModeList(format, 0, &numModes, displayModes);

		if(FAILED(hr))
			AssertFatal(false, "GFXD3D11Device::enumerateVideoModes -> GetDisplayModeList call failure");

		for(U32 numMode = 0; numMode < numModes; ++numMode)
		{
			GFXVideoMode toAdd;

			toAdd.fullScreen = false;
			toAdd.refreshRate = displayModes[numMode].RefreshRate.Numerator / displayModes[numMode].RefreshRate.Denominator;
			toAdd.resolution.x = displayModes[numMode].Width;
			toAdd.resolution.y = displayModes[numMode].Height;
			mVideoModes.push_back(toAdd);
		}

		delete displayModes;
		pOutput->Release();
		EnumAdapter->Release();
   }

   DXGIFactory->Release();
}

void GFXD3D11Device::init(const GFXVideoMode &mode, PlatformWindow *window)
{
	AssertFatal(window, "GFXD3D11Device::init - must specify a window!");

	Win32Window *win = static_cast<Win32Window*>(window);
	AssertISV( win, "GFXD3D11Device::init - got a non Win32Window window passed in! Did DX go crossplatform?" );

	HWND winHwnd = win->getHWND();

	DXGI_SWAP_CHAIN_DESC d3dpp = setupPresentParams(mode, winHwnd);
	mMultisampleDesc.Count = d3dpp.SampleDesc.Count;
	mMultisampleDesc.Quality = d3dpp.SampleDesc.Quality;

	UINT createDeviceFlags = 0;
#ifdef TORQUE_DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    IDXGIFactory* DXGIFactory;
	IDXGIAdapter* EnumAdapter;
	HRESULT hres;

	hres = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&DXGIFactory));
	hres = DXGIFactory->EnumAdapters(mAdapterIndex, &EnumAdapter); 

	if(FAILED(hres)) 
	{ 
	    AssertFatal(false, "GFXD3D11Device::init - Unknown graphics adapter found! Wrong index?!");
	}

	DXGIFactory->Release();

    // create a device, device context and swap chain using the information in the d3dpp struct

    hres = D3D11CreateDeviceAndSwapChain(	NULL,	

											/*	
												anis -> you can also pass EnumAdapter instead NULL but it doesn't work if 
												the driver type (next param) is different from D3D_DRIVER_TYPE_UNKNOWN.

												The best solution is to use D3D_DRIVER_TYPE_HARDWARE/D3D_DRIVER_TYPE_REFERENCE as Microsoft recommends.
														
												infos: http://msdn.microsoft.com/en-us/library/windows/desktop/ff476328(v=vs.85).aspx
											*/

#ifdef TORQUE_DEBUG
											D3D_DRIVER_TYPE_REFERENCE,
#else
											D3D_DRIVER_TYPE_HARDWARE,
#endif
											NULL,
											createDeviceFlags,
											NULL,
											NULL,
											D3D11_SDK_VERSION,
											&d3dpp,
											&mSwapChain,
											&mD3DDevice,
											NULL,
											&mD3DDeviceContext);

	if(FAILED(hres))
	{
		AssertFatal(false, "GFXD3D11Device::init - CreateDevice failed!");
	}

	EnumAdapter->Release();

	mTextureManager = new GFXD3D11TextureManager();

	// Now reacquire all the resources we trashed earlier
	reacquireDefaultPoolResources();

	mPixVersion = 5.0;
	mNumRenderTargets = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;

	D3D11_QUERY_DESC queryDesc;
    queryDesc.Query = D3D11_QUERY_OCCLUSION;
    queryDesc.MiscFlags = 0;

	ID3D11Query *testQuery = NULL;

	// detect occlusion query support
	if (SUCCEEDED(mD3DDevice->CreateQuery(&queryDesc, &testQuery))) mOcclusionQuerySupported = true;

	Con::printf("Hardware occlusion query detected: %s", mOcclusionQuerySupported ? "Yes" : "No");
   
	mCardProfiler = new GFXD3D11CardProfiler(mAdapterIndex);
	mCardProfiler->init();

	SAFE_RELEASE(mDeviceDepthStencilView);
    mD3DDeviceContext->OMGetRenderTargets(1, &mDeviceRenderTargetView, &mDeviceDepthStencilView);

	if(FAILED(hres)) 
	{
		AssertFatal(false, "GFXD3D11Device::init - couldn't grab reference to device's depth-stencil surface.");
	}

	mInitialized = true;
	deviceInited();
}

bool GFXD3D11Device::beginSceneInternal() 
{
    return true;
}

GFXWindowTarget * GFXD3D11Device::allocWindowTarget(PlatformWindow *window)
{
	AssertFatal(window,"GFXD3D9Device::allocWindowTarget - no window provided!");

	// Set up a new window target...
	GFXD3D11WindowTarget *gdwt = new GFXD3D11WindowTarget(mSwapChain);
	gdwt->mWindow = window;
	gdwt->mSize = window->getClientExtent();
	gdwt->initPresentationParams();

	// Allocate the device.
	init(window->getVideoMode(), window);

	SAFE_RELEASE(mDeviceDepthStencilView);
    mD3DDeviceContext->OMGetRenderTargets(1, &mDeviceRenderTargetView, &mDeviceDepthStencilView);

	SAFE_RELEASE(mDeviceBackbuffer);
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&mDeviceBackbuffer);

	HRESULT hr = mD3DDevice->CreateRenderTargetView(mDeviceBackbuffer, NULL, &mDeviceRenderTargetView);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Device::allocWindowTarget - CreateRenderTargetView call failure");
	}

	SAFE_RELEASE(mDeviceDepthStencil);

	DXGI_SWAP_CHAIN_DESC d3dpp;
	mSwapChain->GetDesc(&d3dpp);

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width     = d3dpp.BufferDesc.Width;
	depthStencilDesc.Height    = d3dpp.BufferDesc.Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count   = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;

	hr = D3D11DEVICE->CreateTexture2D(&depthStencilDesc, NULL, &mDeviceDepthStencil);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Device::allocWindowTarget - CreateTexture2D call failure");
	}

	hr = mD3DDevice->CreateDepthStencilView(mDeviceDepthStencil, NULL, &mDeviceDepthStencilView);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Device::allocWindowTarget - CreateDepthStencilView call failure");
	}

	gdwt->registerResourceWithDevice(this);
	return gdwt;
}

GFXTextureTarget* GFXD3D11Device::allocRenderToTextureTarget()
{
   GFXD3D11TextureTarget *targ = new GFXD3D11TextureTarget();
   targ->registerResourceWithDevice(this);

   return targ;
}

void GFXD3D11Device::reset(DXGI_SWAP_CHAIN_DESC &d3dpp)
{
   if(!mD3DDevice)
      return;

   mInitialized = false;

   mMultisampleDesc.Count = d3dpp.SampleDesc.Count;
   mMultisampleDesc.Quality = d3dpp.SampleDesc.Quality;

   // Clean up some commonly dangling state. This helps prevents issues with
   // items that are destroyed by the texture manager callbacks and recreated
   // later, but still left bound.
   setVertexBuffer(NULL);
   setPrimitiveBuffer(NULL);
   for(S32 i=0; i<getNumSamplers(); i++)
      setTexture(i, NULL);

   // First release all the stuff we allocated from D3DPOOL_DEFAULT
   releaseDefaultPoolResources();

   DXGI_MODE_DESC mode;
   mode.Format = d3dpp.BufferDesc.Format;
   mode.Height = d3dpp.BufferDesc.Height;
   mode.RefreshRate = d3dpp.BufferDesc.RefreshRate;
   mode.Scaling = d3dpp.BufferDesc.Scaling;
   mode.ScanlineOrdering = d3dpp.BufferDesc.ScanlineOrdering;
   mode.Width = d3dpp.BufferDesc.Width;

   HRESULT hres;

   if(!d3dpp.Windowed)
   {
       hres = mSwapChain->SetFullscreenState(TRUE, NULL);

       if(FAILED(hres))
       {
           AssertFatal(false, "GFXD3D11Device::SetFullscreenState - Reset call failure");
       }
   }
   else
   {
       hres = mSwapChain->SetFullscreenState(FALSE, NULL);

       if(FAILED(hres))
       {
           AssertFatal(false, "GFXD3D11Device::SetFullscreenState - Reset call failure");
       }
   }

   hres = mSwapChain->ResizeTarget(&mode);

   if(FAILED(hres))
   {
       AssertFatal(false, "GFXD3D11Device::ResizeTarget - Reset call failure");
   }

   hres = mSwapChain->ResizeBuffers(d3dpp.BufferCount, d3dpp.BufferDesc.Width, d3dpp.BufferDesc.Height, d3dpp.BufferDesc.Format, d3dpp.Flags);

   if(FAILED(hres))
   {
       AssertFatal(false, "GFXD3D11Device::ResizeBuffers - Reset call failure");
   }

   mInitialized = true;

   // Now re aquire all the resources we trashed earlier
   reacquireDefaultPoolResources();

   // Mark everything dirty and flush to card, for sanity.
   updateStates(true);
}

class GFXPCD3D11RegisterDevice
{
public:
   GFXPCD3D11RegisterDevice()
   {
      GFXInit::getRegisterDeviceSignal().notify(&GFXD3D11Device::enumerateAdapters);
   }
};

static GFXPCD3D11RegisterDevice pPCD3D11RegisterDevice;

//-----------------------------------------------------------------------------
/// Parse command line arguments for window creation
//-----------------------------------------------------------------------------
static void sgPCD3D11DeviceHandleCommandLine(S32 argc, const char **argv)
{
   // anis -> useful to pass parameters by command line for d3d (e.g. -dx9 -dx11)
   for (U32 i = 1; i < argc; i++)
   {
      argv[i];
   }   
}

// Register the command line parsing hook
static ProcessRegisterCommandLine sgCommandLine( sgPCD3D11DeviceHandleCommandLine );

GFXD3D11Device::GFXD3D11Device(U32 index)
{
   mDeviceSwizzle32 = &Swizzles::bgra;
   GFXVertexColor::setSwizzle( mDeviceSwizzle32 );

   mDeviceSwizzle24 = &Swizzles::bgr;

   mAdapterIndex = index;
   mD3DDevice = NULL;
   mD3DDeviceContext = NULL;
   mSwapChain = NULL;
   
   mVolatileVB = NULL;

   mCurrentPB = NULL;
   mDynamicPB = NULL;

   mLastVertShader = NULL;
   mLastPixShader = NULL;

   mCanCurrentlyRender = false;
   mTextureManager = NULL;
   mCurrentStateBlock = NULL;
   mResourceListHead = NULL;

   mPixVersion = 0.0;
   mNumRenderTargets = 0;

   mCardProfiler = NULL;

   mDeviceDepthStencil = NULL;
   mDeviceBackbuffer = NULL;

   mDeviceRenderTargetView = NULL;
   mDeviceDepthStencilView = NULL;

   mCreateFenceType = -1; // Unknown, test on first allocate

   mCurrentConstBuffer = NULL;

   mOcclusionQuerySupported = false;

   for(int i = 0; i < GS_COUNT; ++i)
      mModelViewProjSC[i] = NULL;

   mCurrentShader = NULL;

   // Set up the Enum translation tables
   GFXD3D11EnumTranslate::init();
}

GFXD3D11Device::~GFXD3D11Device() 
{
   // Release our refcount on the current stateblock object
   mCurrentStateBlock = NULL;

   releaseDefaultPoolResources();

   // Free the vertex declarations.
   VertexDeclMap::Iterator iter = mVertexDecls.begin();
   for ( ; iter != mVertexDecls.end(); iter++ )
      delete iter->value;

   // Forcibly clean up the pools
   mVolatileVBList.setSize(0);
   mDynamicPB = NULL;

   // And release our D3D resources.
   SAFE_RELEASE(mDeviceDepthStencil);
   SAFE_RELEASE(mDeviceBackbuffer);
   SAFE_RELEASE(mDeviceRenderTargetView);
   SAFE_RELEASE(mDeviceDepthStencilView);
   SAFE_RELEASE(mSwapChain);
   SAFE_RELEASE(mD3DDeviceContext);
   SAFE_RELEASE(mD3DDevice);

   if( mCardProfiler )
   {
      delete mCardProfiler;
      mCardProfiler = NULL;
   }
}

/*
	GFXD3D11Device::setupGenericShaders

	anis -> used just for draw some ui elements, this implementation avoid to use fixed pipeline functions.
*/

void GFXD3D11Device::setupGenericShaders(GenericShaderType type)
{
   AssertFatal(type != GSTargetRestore, ""); //not used

   if(mGenericShader[GSColor] == NULL)
   {
	  ShaderData *shaderData;

      shaderData = new ShaderData();
      shaderData->setField("DXVertexShaderFile", "shaders/common/fixedFunction/colorV.hlsl");
      shaderData->setField("DXPixelShaderFile", "shaders/common/fixedFunction/colorP.hlsl");
      shaderData->setField("pixVersion", "4.0");
      shaderData->registerObject();
      mGenericShader[GSColor] =  shaderData->getShader();
      mGenericShaderBuffer[GSColor] = mGenericShader[GSColor]->allocConstBuffer();
      mModelViewProjSC[GSColor] = mGenericShader[GSColor]->getShaderConstHandle("$modelView");

      shaderData = new ShaderData();
      shaderData->setField("DXVertexShaderFile", "shaders/common/fixedFunction/modColorTextureV.hlsl");
      shaderData->setField("DXPixelShaderFile", "shaders/common/fixedFunction/modColorTextureP.hlsl");
      shaderData->setField("pixVersion", "4.0");
      shaderData->registerObject();
      mGenericShader[GSModColorTexture] = shaderData->getShader();
      mGenericShaderBuffer[GSModColorTexture] = mGenericShader[GSModColorTexture]->allocConstBuffer();
      mModelViewProjSC[GSModColorTexture] = mGenericShader[GSModColorTexture]->getShaderConstHandle("$modelView");

      shaderData = new ShaderData();
      shaderData->setField("DXVertexShaderFile", "shaders/common/fixedFunction/addColorTextureV.hlsl");
      shaderData->setField("DXPixelShaderFile", "shaders/common/fixedFunction/addColorTextureP.hlsl");
      shaderData->setField("pixVersion", "4.0");
      shaderData->registerObject();
      mGenericShader[GSAddColorTexture] = shaderData->getShader();
      mGenericShaderBuffer[GSAddColorTexture] = mGenericShader[GSAddColorTexture]->allocConstBuffer();
      mModelViewProjSC[GSAddColorTexture] = mGenericShader[GSAddColorTexture]->getShaderConstHandle("$modelView");

      shaderData = new ShaderData();
      shaderData->setField("DXVertexShaderFile", "shaders/common/fixedFunction/textureV.hlsl");
      shaderData->setField("DXPixelShaderFile", "shaders/common/fixedFunction/textureP.hlsl");
      shaderData->setField("pixVersion", "4.0");
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
GFXStateBlockRef GFXD3D11Device::createStateBlockInternal(const GFXStateBlockDesc& desc)
{
   return GFXStateBlockRef(new GFXD3D11StateBlock(desc));
}

/// Activates a stateblock
void GFXD3D11Device::setStateBlockInternal(GFXStateBlock* block, bool force)
{
   AssertFatal(static_cast<GFXD3D11StateBlock*>(block), "Incorrect stateblock type for this device!");
   GFXD3D11StateBlock* d3dBlock = static_cast<GFXD3D11StateBlock*>(block);
   GFXD3D11StateBlock* d3dCurrent = static_cast<GFXD3D11StateBlock*>(mCurrentStateBlock.getPointer());
   if (force)
      d3dCurrent = NULL;
   d3dBlock->activate(d3dCurrent);   
}

/// Called by base GFXDevice to actually set a const buffer
void GFXD3D11Device::setShaderConstBufferInternal(GFXShaderConstBuffer* buffer)
{
   if (buffer)
   {
      PROFILE_SCOPE(GFXD3D11Device_setShaderConstBufferInternal);
      AssertFatal(static_cast<GFXD3D11ShaderConstBuffer*>(buffer), "Incorrect shader const buffer type for this device!");
      GFXD3D11ShaderConstBuffer* d3dBuffer = static_cast<GFXD3D11ShaderConstBuffer*>(buffer);

      d3dBuffer->activate(mCurrentConstBuffer);
      mCurrentConstBuffer = d3dBuffer;
   } else {
      mCurrentConstBuffer = NULL;
   }
}

//-----------------------------------------------------------------------------

void GFXD3D11Device::clear( U32 flags, ColorI color, F32 z, U32 stencil ) 
{
   // Make sure we have flushed our render target state.
   _updateRenderTargets();

   UINT depthstencilFlag = 0;

   const FLOAT clearColor[4] =	{	
									static_cast<F32>(color.red) * (1.0f / 255.0f),
									static_cast<F32>(color.green) * (1.0f / 255.0f),
									static_cast<F32>(color.blue) * (1.0f / 255.0f),
									static_cast<F32>(color.alpha) * (1.0f / 255.0f)
								};

   if( flags & GFXClearTarget )
      mD3DDeviceContext->ClearRenderTargetView(mDeviceRenderTargetView, clearColor);

   if(flags & GFXClearZBuffer)
	   depthstencilFlag |= D3D11_CLEAR_DEPTH;

   if(flags & GFXClearStencil)
	   depthstencilFlag |= D3D11_CLEAR_STENCIL;

   if(depthstencilFlag)
	   mD3DDeviceContext->ClearDepthStencilView(mDeviceDepthStencilView, depthstencilFlag, z, stencil);
}

void GFXD3D11Device::endSceneInternal() 
{
   mCanCurrentlyRender = false;
}

void GFXD3D11Device::_updateRenderTargets()
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
      D3D11_VIEWPORT viewport;

	  viewport.TopLeftX = mViewport.point.x;
      viewport.TopLeftY = mViewport.point.y;
      viewport.Width	= mViewport.extent.x;
      viewport.Height	= mViewport.extent.y;
      viewport.MinDepth	= 0.0;
	  viewport.MaxDepth	= 1.0;

      mD3DDeviceContext->RSSetViewports(1, &viewport);

	  mViewportDirty = false;
   }
}

void GFXD3D11Device::releaseDefaultPoolResources() 
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
   SAFE_RELEASE(mDeviceDepthStencilView);
   SAFE_RELEASE(mDeviceRenderTargetView);

   mD3DDeviceContext->OMSetRenderTargets(1, &mDeviceRenderTargetView, mDeviceDepthStencilView);

   // Set global dirty state so the IB/PB and VB get reset
   mStateDirty = true;
}

void GFXD3D11Device::reacquireDefaultPoolResources() 
{
	// Now do the dynamic index buffers
	if( mDynamicPB == NULL )
		mDynamicPB = new GFXD3D11PrimitiveBuffer(this, 0, 0, GFXBufferTypeDynamic);

	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = sizeof(U16) * MAX_DYNAMIC_INDICES;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	HRESULT hr = D3D11DEVICE->CreateBuffer(&desc, NULL, &mDynamicPB->ib);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Device::reacquireDefaultPoolResources - Failed to allocate dynamic IB");
	}

	SAFE_RELEASE(mDeviceDepthStencilView);
	SAFE_RELEASE(mDeviceRenderTargetView);
    mD3DDeviceContext->OMGetRenderTargets(1, &mDeviceRenderTargetView, &mDeviceDepthStencilView);

	SAFE_RELEASE(mDeviceBackbuffer);
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&mDeviceBackbuffer);

	hr = mD3DDevice->CreateRenderTargetView(mDeviceBackbuffer, NULL, &mDeviceRenderTargetView);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Device::reacquireDefaultPoolResources - CreateRenderTargetView call failure");
	}

	SAFE_RELEASE(mDeviceDepthStencil);

	DXGI_SWAP_CHAIN_DESC d3dpp;
	mSwapChain->GetDesc(&d3dpp);

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width     = d3dpp.BufferDesc.Width;
	depthStencilDesc.Height    = d3dpp.BufferDesc.Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count   = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;

	hr = D3D11DEVICE->CreateTexture2D(&depthStencilDesc, NULL, &mDeviceDepthStencil);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Device::reacquireDefaultPoolResources - CreateTexture2D call failure");
	}

	hr = mD3DDevice->CreateDepthStencilView(mDeviceDepthStencil, NULL, &mDeviceDepthStencilView);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "GFXD3D11Device::reacquireDefaultPoolResources - CreateDepthStencilView call failure");
	}

	mDisplayMode.Format = d3dpp.BufferDesc.Format;
	mDisplayMode.Height = d3dpp.BufferDesc.Height;
	mDisplayMode.RefreshRate = d3dpp.BufferDesc.RefreshRate;
	mDisplayMode.Scaling = d3dpp.BufferDesc.Scaling;
	mDisplayMode.ScanlineOrdering = d3dpp.BufferDesc.ScanlineOrdering;
	mDisplayMode.Width = d3dpp.BufferDesc.Width;

    if(mTextureManager)
        mTextureManager->resurrect();
}

GFXD3D11VertexBuffer* GFXD3D11Device::findVBPool(const GFXVertexFormat *vertexFormat, U32 vertsNeeded)
{
   PROFILE_SCOPE(GFXD3D11Device_findVBPool);

   for(U32 i=0; i<mVolatileVBList.size(); i++)
      if( mVolatileVBList[i]->mVertexFormat.isEqual(*vertexFormat))
         return mVolatileVBList[i];

   return NULL;
}

GFXD3D11VertexBuffer * GFXD3D11Device::createVBPool(const GFXVertexFormat *vertexFormat, U32 vertSize)
{
	PROFILE_SCOPE(GFXD3D11Device_createVBPool);

	// this is a bit funky, but it will avoid problems with (lack of) copy constructors
	//    with a push_back() situation
	mVolatileVBList.increment();
	StrongRefPtr<GFXD3D11VertexBuffer> newBuff;
	mVolatileVBList.last() = new GFXD3D11VertexBuffer();
	newBuff = mVolatileVBList.last();

	newBuff->mNumVerts   = 0;
	newBuff->mBufferType = GFXBufferTypeVolatile;
	newBuff->mVertexFormat.copy(*vertexFormat);
	newBuff->mVertexSize = vertSize;
	newBuff->mDevice = this;

	// Requesting it will allocate it.
	vertexFormat->getDecl();

	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = vertSize * MAX_DYNAMIC_VERTS;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	HRESULT hr = mD3DDevice->CreateBuffer(&desc, NULL, &newBuff->vb);

	if(FAILED(hr)) 
	{
		AssertFatal(false, "Failed to allocate dynamic VB");
	}

	return newBuff;
}

void GFXD3D11Device::setClipRect(const RectI &inRect) 
{
   // We transform the incoming rect by the view 
   // matrix first, so that it can be used to pan
   // and scale the clip rect.
   //
   // This is currently used to take tiled screenshots.
   Point3F pos( inRect.point.x, inRect.point.y, 0.0f );
   Point3F extent( inRect.extent.x, inRect.extent.y, 0.0f );
   getViewMatrix().mulP( pos );
   getViewMatrix().mulV( extent );  
   RectI rect( pos.x, pos.y, extent.x, extent.y );

   // Clip the rect against the renderable size.
   Point2I size = mCurrentRT->getSize();

   RectI maxRect(Point2I(0,0), size);
   rect.intersect(maxRect);

   mClipRect = rect;

   F32 l = F32( mClipRect.point.x );
   F32 r = F32( mClipRect.point.x + mClipRect.extent.x );
   F32 b = F32( mClipRect.point.y + mClipRect.extent.y );
   F32 t = F32( mClipRect.point.y );

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

   setProjectionMatrix( mTempMatrix );

   // Set up world/view matrix
   mTempMatrix.identity();   
   setWorldMatrix( mTempMatrix );

   setViewport( mClipRect );
}

void GFXD3D11Device::setVertexStream(U32 stream, GFXVertexBuffer *buffer)
{
	GFXD3D11VertexBuffer *d3dBuffer = static_cast<GFXD3D11VertexBuffer*>(buffer);

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

	U32 offset = 0;

	if(d3dBuffer && stream != 0)
		offset = d3dBuffer->mVolatileStart * d3dBuffer->mVertexSize;

    mD3DDeviceContext->IASetVertexBuffers(	0, 
											stream,
											d3dBuffer ? reinterpret_cast<ID3D11Buffer*const*>(d3dBuffer->vb) : NULL,
											d3dBuffer ? &d3dBuffer->mVertexSize : 0,
											&offset );
}

void GFXD3D11Device::setVertexStreamFrequency(U32 stream, U32 frequency)
{

}

void GFXD3D11Device::_setPrimitiveBuffer(GFXPrimitiveBuffer *buffer)
{
   mCurrentPB = static_cast<GFXD3D11PrimitiveBuffer *>(buffer);

   mD3DDeviceContext->IASetIndexBuffer(mCurrentPB->ib, DXGI_FORMAT_R16_UINT, 0);
}

void GFXD3D11Device::drawPrimitive(GFXPrimitiveType primType, U32 vertexStart, U32 primitiveCount)
{
   // This is done to avoid the function call overhead if possible
   if(mStateDirty)
      updateStates();
   if (mCurrentShaderConstBuffer)
      setShaderConstBufferInternal(mCurrentShaderConstBuffer);

   if (mVolatileVB)
      vertexStart += mVolatileVB->mVolatileStart;

   mD3DDeviceContext->IASetPrimitiveTopology(GFXD3D11PrimType[primType]);
   mD3DDeviceContext->Draw(primitiveCount, vertexStart);

   mDeviceStatistics.mDrawCalls++;
   if (mVertexBufferFrequency[0] > 1)
      mDeviceStatistics.mPolyCount += primitiveCount * mVertexBufferFrequency[0];
   else
      mDeviceStatistics.mPolyCount += primitiveCount;
}

void GFXD3D11Device::drawIndexedPrimitive( GFXPrimitiveType primType, 
                                          U32 startVertex, 
                                          U32 minIndex, 
                                          U32 numVerts, 
                                          U32 startIndex, 
                                          U32 primitiveCount ) 
{
   // This is done to avoid the function call overhead if possible
   if(mStateDirty)
      updateStates();
   if(mCurrentShaderConstBuffer)
      setShaderConstBufferInternal(mCurrentShaderConstBuffer);

   AssertFatal( mCurrentPB != NULL, "Trying to call drawIndexedPrimitive with no current index buffer, call setIndexBuffer()" );

   if ( mVolatileVB )
      startVertex += mVolatileVB->mVolatileStart;

   mD3DDeviceContext->IASetPrimitiveTopology(GFXD3D11PrimType[primType]);
   mD3DDeviceContext->DrawIndexed(primitiveCount, mCurrentPB->mVolatileStart + startIndex, startVertex);

   mDeviceStatistics.mDrawCalls++;
   if (mVertexBufferFrequency[0] > 1)
      mDeviceStatistics.mPolyCount += primitiveCount * mVertexBufferFrequency[0];
   else
      mDeviceStatistics.mPolyCount += primitiveCount;
}

GFXShader* GFXD3D11Device::createShader()
{
   GFXD3D11Shader* shader = new GFXD3D11Shader();
   shader->registerResourceWithDevice(this);
   return shader;
}

//-----------------------------------------------------------------------------
// Set shader - this function exists to make sure this is done in one place,
//              and to make sure redundant shader states are not being
//              sent to the card.
//-----------------------------------------------------------------------------
void GFXD3D11Device::setShader(GFXShader *shader)
{
   if(mCurrentShader == shader)
       return;

   if(shader)
   {
	   GFXD3D11Shader *d3dShader = static_cast<GFXD3D11Shader*>(shader);

	   if(d3dShader->mPixShader != mLastPixShader)
	   {
		  mD3DDeviceContext->PSSetShader(d3dShader->mPixShader, NULL, 0);
		  mLastPixShader = d3dShader->mPixShader;
	   }

	   if(d3dShader->mVertShader != mLastVertShader)
	   {
		  mD3DDeviceContext->VSSetShader(d3dShader->mVertShader, NULL, 0);
		  mLastVertShader = d3dShader->mVertShader;
	   }

      mCurrentShader = shader;
   }

   else
   {
       setupGenericShaders();
   }
}

GFXPrimitiveBuffer * GFXD3D11Device::allocPrimitiveBuffer(U32 numIndices, U32 numPrimitives, GFXBufferType bufferType)
{
   // Allocate a buffer to return
   GFXD3D11PrimitiveBuffer * res = new GFXD3D11PrimitiveBuffer(this, numIndices, numPrimitives, bufferType);

   // Determine usage flags
   D3D11_USAGE usage = D3D11_USAGE_DEFAULT;

   // Assumptions:
   //    - static buffers are write once, use many
   //    - dynamic buffers are write many, use many
   //    - volatile buffers are write once, use once
   // You may never read from a buffer.
   switch(bufferType)
   {
   case GFXBufferTypeStatic:
      usage = D3D11_USAGE_IMMUTABLE;
      break;

   case GFXBufferTypeDynamic:
   case GFXBufferTypeVolatile:
      usage = D3D11_USAGE_DYNAMIC;
      break;
   }

   // Register resource
   res->registerResourceWithDevice(this);

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
		D3D11_BUFFER_DESC desc;
      ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(U16) * numIndices;
		//desc.Usage = usage;
		desc.Usage = D3D11_USAGE_DEFAULT;
      desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0; //D3D11_CPU_ACCESS_WRITE; // We never allow reading from a primitive buffer.
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		HRESULT hr = mD3DDevice->CreateBuffer(&desc, NULL, &res->ib);

		if(FAILED(hr)) 
		{
			AssertFatal(false, "Failed to allocate an index buffer.");
		}
   }

   return res;
}

GFXVertexBuffer * GFXD3D11Device::allocVertexBuffer(U32 numVerts, const GFXVertexFormat *vertexFormat, U32 vertSize, GFXBufferType bufferType)
{
   PROFILE_SCOPE(GFXD3D11Device_allocVertexBuffer);

   GFXD3D11VertexBuffer *res = new GFXD3D11VertexBuffer( this, 
                                                         numVerts, 
                                                         vertexFormat, 
                                                         vertSize, 
                                                         bufferType );

   // Determine usage flags
   D3D11_USAGE usage = D3D11_USAGE_DEFAULT;

   res->mNumVerts = 0;

   // Assumptions:
   //    - static buffers are write once, use many
   //    - dynamic buffers are write many, use many
   //    - volatile buffers are write once, use once
   // You may never read from a buffer.

   switch(bufferType)
   {
   case GFXBufferTypeStatic:
      usage = D3D11_USAGE_IMMUTABLE;
      break;

   case GFXBufferTypeDynamic:
   case GFXBufferTypeVolatile:
	  usage = D3D11_USAGE_DYNAMIC;
      break;
   }

   // Register resource
   res->registerResourceWithDevice(this);

   // Create vertex buffer
   if(bufferType == GFXBufferTypeVolatile)
   {
        // NOTE: Volatile VBs are pooled and will be allocated at lock time.
        AssertFatal(numVerts <= MAX_DYNAMIC_VERTS, "GFXD3D11Device::allocVertexBuffer - Volatile vertex buffer is too big... see MAX_DYNAMIC_VERTS!");
   }
   else
   {
		// Requesting it will allocate it.
		vertexFormat->getDecl();

		// Get a new buffer...
		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = vertSize * numVerts;
		desc.Usage = usage;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // We never allow reading from a vertex buffer.
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		HRESULT hr = mD3DDevice->CreateBuffer(&desc, NULL, &res->vb);

		if(FAILED(hr)) 
		{
			AssertFatal(false, "Failed to allocate VB");
		}
   }

   res->mNumVerts = numVerts;
   return res;
}

GFXVertexDecl* GFXD3D11Device::allocVertexDecl(const GFXVertexFormat *vertexFormat)
{
   PROFILE_SCOPE(GFXD3D11Device_allocVertexDecl);

   // First check the map... you shouldn't allocate VBs very often
   // if you want performance.  The map lookup should never become
   // a performance bottleneck.
   D3D11VertexDecl *decl = mVertexDecls[vertexFormat->getDescription()];
   if ( decl )
      return decl;

   // Setup the declaration struct.
   U32 elemCount = vertexFormat->getElementCount();
   U32 offsets[4] = { 0 };
   U32 stream;

   D3D11_INPUT_ELEMENT_DESC* vd = new D3D11_INPUT_ELEMENT_DESC[elemCount];

   for (U32 i=0; i < elemCount; i++)
   {
      const GFXVertexElement &element = vertexFormat->getElement(i);
      
      stream = element.getStreamIndex();

      vd[i].AlignedByteOffset = offsets[stream];
      vd[i].Format = GFXD3D11DeclType[element.getType()];
      vd[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
      vd[i].InstanceDataStepRate = 0;
      vd[i].InputSlot = i;

      // We force the usage index of 0 for everything but 
      // texture coords for now... this may change later.
      vd[i].SemanticIndex = 0;

      if (element.isSemantic(GFXSemantic::POSITION))
         vd[i].SemanticName = GFXSemantic::POSITION;
      else if (element.isSemantic(GFXSemantic::NORMAL))
         vd[i].SemanticName = GFXSemantic::NORMAL;
      else if (element.isSemantic( GFXSemantic::COLOR))
         vd[i].SemanticName = GFXSemantic::COLOR;
      else if (element.isSemantic( GFXSemantic::TANGENT))
         vd[i].SemanticName = GFXSemantic::TANGENT;
      else if (element.isSemantic( GFXSemantic::BINORMAL))
         vd[i].SemanticName = GFXSemantic::BINORMAL;
      else
      {
         // Anything that falls thru to here will be a texture coord.
         vd[i].SemanticName = GFXSemantic::TEXCOORD;
         vd[i].SemanticIndex = element.getSemanticIndex();
      }

      offsets[stream] += element.getSizeInBytes();
   }

   decl = new D3D11VertexDecl();

   String code;
   if ( !mCurrentShader )
      setupGenericShaders();
   mCurrentShader->getCompiled(code);
   HRESULT hr = mD3DDevice->CreateInputLayout(vd, elemCount, code.c_str(), code.length(), &decl->decl);

   if(FAILED(hr)) 
   {
       AssertFatal(false, "GFXD3D11Device::allocVertexDecl - CreateInputLayout call failure!");
   }

   delete [] vd;

   // Store it in the cache.
   mVertexDecls[vertexFormat->getDescription()] = decl;

   return decl;
}

void GFXD3D11Device::setVertexDecl( const GFXVertexDecl *decl )
{
   ID3D11InputLayout *dx11Decl = NULL;
   if (decl)
      dx11Decl = static_cast<const D3D11VertexDecl*>(decl)->decl;

   mD3DDeviceContext->IASetInputLayout(dx11Decl);
}

//-----------------------------------------------------------------------------
// This function should ONLY be called from GFXDevice::updateStates() !!!
//-----------------------------------------------------------------------------
void GFXD3D11Device::setTextureInternal(U32 textureUnit, const GFXTextureObject *texture)
{
	if(texture == NULL)
	{
		ID3D11ShaderResourceView* pViews[1] = { NULL };
		mD3DDeviceContext->PSSetShaderResources(0, 1, &pViews[0]);
		return;
	}

	GFXD3D11TextureObject *tex = (GFXD3D11TextureObject*)texture;
	mD3DDeviceContext->PSSetShaderResources(textureUnit, 1, tex->getSurfacePtr());
}

GFXFence *GFXD3D11Device::createFence()
{
   // Figure out what fence type we should be making if we don't know
   if(mCreateFenceType == -1)
   {
	  D3D11_QUERY_DESC desc;
	  desc.MiscFlags = 0;
	  desc.Query = D3D11_QUERY_EVENT;

	  ID3D11Query *testQuery = NULL;

	  HRESULT hRes = mD3DDevice->CreateQuery(&desc, &testQuery);

	  if(FAILED(hRes))
	  {
		  mCreateFenceType = true;
	  }

	  else
	  {
		  mCreateFenceType = false;
	  }

      SAFE_RELEASE(testQuery);
   }

   // Cool, use queries
   if(!mCreateFenceType)
   {
      GFXFence* fence = new GFXD3D11QueryFence(this);
      fence->registerResourceWithDevice(this);
      return fence;
   }

   // CodeReview: At some point I would like a specialized D3D11 implementation of
   // the method used by the general fence, only without the overhead incurred 
   // by using the GFX constructs. Primarily the lock() method on texture handles
   // will do a data copy, and this method doesn't require a copy, just a lock
   // [5/10/2007 Pat]
   GFXFence* fence = new GFXGeneralFence(this);
   fence->registerResourceWithDevice(this);
   return fence;
}

GFXOcclusionQuery* GFXD3D11Device::createOcclusionQuery()
{  
   GFXOcclusionQuery *query;
   if (mOcclusionQuerySupported)
      query = new GFXD3D11OcclusionQuery(this);
   else
      return NULL;      

   query->registerResourceWithDevice(this);
   return query;
}

GFXCubemap * GFXD3D11Device::createCubemap()
{
   GFXD3D11Cubemap* cube = new GFXD3D11Cubemap();
   cube->registerResourceWithDevice(this);
   return cube;
}