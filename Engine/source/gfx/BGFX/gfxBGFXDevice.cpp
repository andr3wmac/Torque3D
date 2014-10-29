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

#include "platform/platform.h"
#include "gfx/BGFX/gfxBGFXDevice.h"
#include "gfx/BGFX/gfxBGFXTextureManager.h"
#include "gfx/BGFX/gfxBGFXTextureTarget.h"
#include "gfx/BGFX/gfxBGFXVertexBuffer.h"
#include "gfx/BGFX/gfxBGFXPrimitiveBuffer.h"
#include "gfx/BGFX/gfxBGFXStateBlock.h"
#include "gfx/BGFX/gfxBGFXCardProfiler.h"
#include "gfx/BGFX/gfxBGFXCubemap.h"
#include "gfx/BGFX/gfxBGFXShader.h"
#include "gfx/BGFX/gfxBGFXDrawUtil.h"

#include "core/fileObject.h"
#include "core/strings/stringFunctions.h"
#include "gfx/gfxCubemap.h"
#include "gfx/screenshot.h"
#include "gfx/gfxPrimitiveBuffer.h"
#include "gfx/gfxCardProfile.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/bitmap/gBitmap.h"
#include "core/util/safeDelete.h"
#include "windowManager/win32/win32Window.h"
#include "windowManager/platformWindowMgr.h"

#include <font/font_manager.h>
#include <font/text_buffer_manager.h>

#include <bgfx.h>
#include <bgfxplatform.h>
#include <bx/fpumath.h>

// --------------------------------------
// TEMP TEST CUBE straight out of bgfx.
// --------------------------------------
struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

static PosColorVertex s_cubeVertices[8] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeIndices[36] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};
// --------------------------------------

GFXAdapter::CreateDeviceInstanceDelegate GFXBGFXDevice::mCreateDeviceInstance(GFXBGFXDevice::createInstance); 

GFXDevice *GFXBGFXDevice::createInstance( U32 adapterIndex )
{
   return new GFXBGFXDevice();
}

GFXBGFXDevice::GFXBGFXDevice()
{
   clip.set(0, 0, 800, 800);

   mTextureManager = new GFXBGFXTextureManager();
   gScreenShot = new ScreenShot();
   mCardProfiler = new GFXBGFXCardProfiler();
   mCardProfiler->init();
   mWindowWidth = 1;
   mWindowHeight = 1;
   testCounter = 0;
   mWindow = NULL;

   // Previous Clear State
   prevFlags = 0;
   prevColor = 0;
   prevZ = 0.0f;

   projMat = NULL;
   viewMat = NULL;
   worldMat = NULL;

   internalTex.idx = bgfx::invalidHandle;

   fontManager = NULL;
	textBufferManager = NULL;
   ttFontHandle.idx = bgfx::invalidHandle;
   textBuffer.idx = bgfx::invalidHandle;

   nvgFont = -1;
   nvgInFrame = false;

   mTextureFlags = 0;
   mState = 0;
   mStateBlock = NULL;
   mVertexBuffer = NULL;
   mVertexBufferFreq = 0;
   mShader = NULL;
   mCurrentPB = NULL;
}

GFXBGFXDevice::~GFXBGFXDevice()
{
   bgfx::destroyUniform(u_texColor);
   bgfx::shutdown();
}

GFXVertexBuffer *GFXBGFXDevice::allocVertexBuffer( U32 numVerts, 
                                                   const GFXVertexFormat *vertexFormat,
                                                   U32 vertSize, 
                                                   GFXBufferType bufferType ) 
{
   return new GFXBGFXVertexBuffer(GFX, numVerts, vertexFormat, vertSize, bufferType);
}

void GFXBGFXDevice::setVertexStream( U32 stream, GFXVertexBuffer *buffer )
{
   mVertexBuffer = static_cast<GFXBGFXVertexBuffer*>(buffer);
   //Con::printf("[BGFX] Changing Vertex Stream.");
}

void GFXBGFXDevice::setVertexStreamFrequency( U32 stream, U32 frequency )
{
   mVertexBufferFreq = frequency;
}

GFXPrimitiveBuffer *GFXBGFXDevice::allocPrimitiveBuffer( U32 numIndices, 
                                                         U32 numPrimitives, 
                                                         GFXBufferType bufferType) 
{
   return new GFXBGFXPrimitiveBuffer(GFX, numIndices, numPrimitives, bufferType);
}

GFXCubemap* GFXBGFXDevice::createCubemap()
{ 
   return new GFXBGFXCubemap(); 
};

void GFXBGFXDevice::enumerateAdapters( Vector<GFXAdapter*> &adapterList )
{
   bgfx::RendererType::Enum renderers[bgfx::RendererType::Count];
	U8 numRenderers = bgfx::getSupportedRenderers(renderers);
   for (U8 n = 0; n < numRenderers; ++n)
   {
      // Add the BGFX renderer
      GFXAdapter *toAdd = new GFXAdapter();

      toAdd->mIndex = 0;
      toAdd->mType  = BGFXDevice;
      toAdd->mShaderModel = 5.0f;
      toAdd->mCreateDeviceInstanceDelegate = mCreateDeviceInstance;

      GFXVideoMode vm;
      vm.bitDepth = 32;
      vm.resolution.set(800,600);
      toAdd->mAvailableModes.push_back(vm);
      
      switch(renderers[n])
      {
         case bgfx::RendererType::Direct3D11:
            dStrcpy(toAdd->mName, "BGFX - Direct3D11");
            break;
         case bgfx::RendererType::Direct3D9:
            dStrcpy(toAdd->mName, "BGFX - Direct3D9");
            break;
         case bgfx::RendererType::OpenGL:
            dStrcpy(toAdd->mName, "BGFX - OpenGL");
            break;
         case bgfx::RendererType::OpenGLES:
            dStrcpy(toAdd->mName, "BGFX - OpenGLES");
            break;
      }

      adapterList.push_back(toAdd);
   }


}

void GFXBGFXDevice::setLightInternal(U32 lightStage, const GFXLightInfo light, bool lightEnable)
{

}

void GFXBGFXDevice::init( const GFXVideoMode &mode, PlatformWindow *window )
{
   Win32Window *win = dynamic_cast<Win32Window*>( window );
   AssertISV( win, "GFXD3D11Device::init - got a non Win32Window window passed in! Did DX go crossplatform?" );
   HWND winHwnd = win->getHWND();

   mWindow = window;
   mWindowWidth = mode.resolution.x;
	mWindowHeight = mode.resolution.y;
	U32 debug = BGFX_DEBUG_TEXT;
	U32 reset = BGFX_RESET_NONE;

   bgfx::winSetHwnd(winHwnd);
   bgfx::init(bgfx::RendererType::Direct3D9);
	bgfx::reset(mWindowWidth, mWindowHeight, reset);

	// Enable debug text.
	//bgfx::setDebug(debug);

   u_texColor = bgfx::createUniform("u_texColor", bgfx::UniformType::Uniform1iv);

   bgfx::setViewSeq(0, true);
   nvgContext = nvgCreate(mWindowWidth, mWindowHeight, 0 , 0);
   //bgfx::setViewSeq(2, true);

   nvgCreateFont(nvgContext, "sans", "fonts/roboto-regular.ttf");
   nvgCreateFont(nvgContext, "Lucida Console", "fonts/lucon.ttf");
   nvgCreateFont(nvgContext, "Arial", "fonts/arial.ttf");
   nvgCreateFont(nvgContext, "Arial Bold", "fonts/arialbd.ttf");
   nvgCreateFont(nvgContext, "Arial Italic", "fonts/ariali.ttf");
   
   GFXBGFXStateBlock::initEnumTranslate();
   //createTestFont();

   initTestCube();

   mInitialized = true;
   deviceInited();


}

GFXStateBlockRef GFXBGFXDevice::createStateBlockInternal(const GFXStateBlockDesc& desc)
{
   return GFXStateBlockRef(new GFXBGFXStateBlock(desc));
}

//
// Register this device with GFXInit
//
class GFXBGFXRegisterDevice
{
public:
   GFXBGFXRegisterDevice()
   {
      GFXInit::getRegisterDeviceSignal().notify(&GFXBGFXDevice::enumerateAdapters);
   }
};

static GFXBGFXRegisterDevice pBGFXRegisterDevice;

GFXWindowTarget *GFXBGFXDevice::allocWindowTarget(PlatformWindow *window)
{
   AssertFatal(window,"GFXD3D11Device::allocWindowTarget - no window provided!");
   init(window->getVideoMode(), window);

   GFXBGFXWindowTarget* newWindow = new GFXBGFXWindowTarget(window);
   return newWindow;
};

bool GFXBGFXDevice::beginSceneInternal() 
{
   Point2I res = mWindow->getVideoMode().resolution;
   if ( mWindowWidth != res.x || mWindowHeight != res.y )
   {
      mWindowWidth = res.x;
      mWindowHeight = res.y;
      bgfx::reset(mWindowWidth, mWindowHeight, BGFX_RESET_NONE);
   }

	// Set view 0 default viewport.
	bgfx::setViewRect(0, 0, 0, mWindowWidth, mWindowHeight);

   // Test GUI.
   //bgfx::setViewRect(1, 0, 0, mWindowWidth, mWindowHeight);

   //Con::printf("[BGFX] Beginning scene");
   mCanCurrentlyRender = true;
   return mCanCurrentlyRender;      
}

NVGcontext* GFXBGFXDevice::getNVGContext()
{
   if ( nvgFont == -1 )
   {
      nvgFont = nvgCreateFont(nvgContext, "sans-bold", "fonts/roboto-bold.ttf");
   }

   if ( !nvgInFrame )
   {
      nvgBeginFrame(nvgContext, mWindowWidth, mWindowHeight, 1.0f, NVG_STRAIGHT_ALPHA);
      nvgInFrame = true;
   }
   return nvgContext;
}

void GFXBGFXDevice::endNVGFrame()
{
   if ( nvgInFrame )
   {
      nvgEndFrame(nvgContext);
      nvgInFrame = false;
   }
}

void GFXBGFXDevice::drawNGV()
{
   if ( nvgFont == -1 )
   {
      nvgFont = nvgCreateFont(nvgContext, "sans-bold", "fonts/roboto-bold.ttf");
   }

   const char* title = "Torque NanoVG Test";
   float x = 50.0f;
   float y = 50.0f; 
   float w = 400.0f;
   float h = 250.0f;
   float cornerRadius = 3.0f;
   struct NVGpaint shadowPaint;
	struct NVGpaint headerPaint;

   nvgBeginFrame(nvgContext, mWindowWidth, mWindowHeight, 1.0f, NVG_STRAIGHT_ALPHA);

   nvgBeginPath(nvgContext);
	nvgRoundedRect(nvgContext, x, y, w, h, cornerRadius);
	nvgFillColor(nvgContext, nvgRGBA(28,30,34,192));
	nvgFill(nvgContext);

   shadowPaint = nvgBoxGradient(nvgContext, x,y+2, w,h, cornerRadius*2, 10, nvgRGBA(0,0,0,128), nvgRGBA(0,0,0,0));
	nvgBeginPath(nvgContext);
	nvgRect(nvgContext, x-10,y-10, w+20,h+30);
	nvgRoundedRect(nvgContext, x,y, w,h, cornerRadius);
	nvgPathWinding(nvgContext, NVG_HOLE);
	nvgFillPaint(nvgContext, shadowPaint);
	nvgFill(nvgContext);

	// Header
	headerPaint = nvgLinearGradient(nvgContext, x,y,x,y+15, nvgRGBA(255,0,0,100), nvgRGBA(0,0,0,16));
	nvgBeginPath(nvgContext);
	nvgRoundedRect(nvgContext, x+1,y+1, w-2,30, cornerRadius-1);
	nvgFillPaint(nvgContext, headerPaint);
	nvgFill(nvgContext);
	nvgBeginPath(nvgContext);
	nvgMoveTo(nvgContext, x+0.5f, y+0.5f+30);
	nvgLineTo(nvgContext, x+0.5f+w-1, y+0.5f+30);
	nvgStrokeColor(nvgContext, nvgRGBA(0,0,0,32));
	nvgStroke(nvgContext);

   // Test
   nvgEndFrame(nvgContext);
   nvgBeginFrame(nvgContext, mWindowWidth, mWindowHeight, 1.0f, NVG_STRAIGHT_ALPHA);

   nvgFontSize(nvgContext, 48.0f);
   U32 testFont = nvgFindFont(nvgContext, "sans");
	nvgFontFaceId(nvgContext, nvgFont);
	nvgTextAlign(nvgContext,NVG_ALIGN_CENTER|NVG_ALIGN_MIDDLE);

	//nvgFontBlur(nvgContext, 2);
	nvgFillColor(nvgContext, nvgRGBA(255,255,255,128));
	nvgText(nvgContext, x+w/2,y+16+1, title, NULL);

	//nvgFontBlur(nvgContext, 0);
	nvgFillColor(nvgContext, nvgRGBA(255,0,0,255));
	//nvgText(nvgContext, 10, 10, "fuck yo SHIT NiggA", NULL);

	nvgFontSize(nvgContext, 20.0f);
	nvgFontFaceId(nvgContext, nvgFont);
	nvgTextAlign(nvgContext,NVG_ALIGN_LEFT|NVG_ALIGN_MIDDLE);
	nvgFillColor(nvgContext, nvgRGBA(255,255,255,160));
	nvgText(nvgContext, x+w*0.5f,y+h*0.5f,"TURN DOWN FOR WhAT?", NULL);

   nvgEndFrame(nvgContext);
}

//-----------------------------------------------------------------------------

void GFXBGFXDevice::endSceneInternal() 
{
   //Con::printf("[BGFX] Scene End.");

   // Testing Text Manager
   /*if ( textBufferManager && textBuffer.idx != bgfx::invalidHandle )
   {
      F32 centering = 0.5f;
      F32 proj[16];
		mtxOrtho(proj, centering, mWindowWidth + centering, mWindowHeight + centering, centering, -1.0f, 1.0f);
      bgfx::setViewTransform(1, MatrixF::Identity, proj);
      textBufferManager->submitTextBuffer(textBuffer, 1);
   }*/

   //drawNGV();

   if ( nvgInFrame )
   {
      nvgEndFrame(nvgContext);
      nvgInFrame = false;
   }

   drawTestCube();

	// Advance to next frame. Rendering thread will be kicked to 
	// process submitted rendering primitives.
	bgfx::frame();

   mCanCurrentlyRender = false;
}

void GFXBGFXDevice::setVideoMode( const GFXVideoMode &mode )
{
   mWindowWidth = mode.resolution.x;
   mWindowHeight = mode.resolution.y;
}

void GFXBGFXDevice::clear( U32 flags, ColorI color, F32 z, U32 stencil )
{
   // Make sure we have flushed our render target state.
   //_updateRenderTargets();
   
   // Clear state is a new concept here. The idea is to only set it when
   // you have to. You can dummy call submit() to force a clear if nothing
   // else gets rendered. 
   U8 realFlags = 0;
   U32 realColor = BGFXCOLOR_RGBA(color.red, color.green, color.blue, color.alpha);

   if( flags & GFXClearTarget )
      realFlags |= BGFX_CLEAR_COLOR_BIT;

   if( flags & GFXClearZBuffer )
      realFlags |= BGFX_CLEAR_DEPTH_BIT;

   if( flags & GFXClearStencil )
      realFlags |= BGFX_CLEAR_STENCIL_BIT;

   // Check if theres any need to update the clear state.
   if ( realFlags != prevFlags || realColor != prevColor || z != prevZ )
   {
      prevFlags = realFlags;
      prevColor = realColor;
      prevZ = z;

	   // Set view 0 clear state.
	   bgfx::setViewClear(0
		   , prevFlags
		   , prevColor
		   , prevZ
		   , 0
		   );
   }

	// This dummy draw call is here to make sure that view 0 is cleared
	// if no other draw calls are submitted to view 0.
	bgfx::submit(0);

	// Use debug font to print information about this example.
   //F32 fps_real = Con::getFloatVariable("fps::real");
	//bgfx::dbgTextClear();
	//bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx Torque3D");
	//bgfx::dbgTextPrintf(0, 2, 0x6f, "FPS: %f", fps_real);
}

GFXVertexDecl* GFXBGFXDevice::allocVertexDecl( const GFXVertexFormat *vertexFormat )
{
   PROFILE_SCOPE( GFXD3D9Device_allocVertexDecl );

   // First check the map... you shouldn't allocate VBs very often
   // if you want performance.  The map lookup should never become
   // a performance bottleneck.
   BGFXVertexDecl* vertDecl = mVertexDecls[vertexFormat->getDescription()];
   if ( vertDecl )
      return vertDecl;

   bgfx::VertexDecl* decl = new bgfx::VertexDecl();
   decl->begin();

   Con::printf("[bgfx] Semantic: Layout START");

   // Setup the declaration struct.
   U32 elemCount = vertexFormat->getElementCount();
   for ( U32 i=0; i < elemCount; i++ )
   {
      Con::printf("[bgfx] Semantic: New Element");
      const GFXVertexElement &element = vertexFormat->getElement( i );

      U8 itemType = 0;
      U8 itemCount = 0;
      bool normalized = false;
      switch(element.getType())
      {
         case GFXDeclType::GFXDeclType_Color:
            itemType = bgfx::AttribType::Uint8;
            itemCount = 4;
            normalized = true;
            break;

         case GFXDeclType::GFXDeclType_Float:
            itemType = bgfx::AttribType::Float;
            itemCount = 1;
            break;

         case GFXDeclType::GFXDeclType_Float2:
            itemType = bgfx::AttribType::Float;
            itemCount = 2;
            break;

         case GFXDeclType::GFXDeclType_Float3:
            itemType = bgfx::AttribType::Float;
            itemCount = 3;
            break;

         case GFXDeclType::GFXDeclType_Float4:
            itemType = bgfx::AttribType::Float;
            itemCount = 4;
            break;

         default:
            Con::printf("UNKNOWN ELEMENT TYPE IN VERTEX DECLARATION!");
            break;
      }

      if ( element.isSemantic( GFXSemantic::POSITION ) )
      {
         Con::printf("[bgfx] Semantic: Position");
         decl->add(bgfx::Attrib::Position, itemCount, (bgfx::AttribType::Enum)itemType, normalized);
      }
      else if ( element.isSemantic( GFXSemantic::NORMAL ) )
      {
         Con::printf("[bgfx] Semantic: Normal");
         decl->add(bgfx::Attrib::Normal, itemCount, (bgfx::AttribType::Enum)itemType, normalized);
      }
      else if ( element.isSemantic( GFXSemantic::COLOR ) )
      {
         Con::printf("[bgfx] Semantic: Color");
         decl->add(bgfx::Attrib::Color0, itemCount, (bgfx::AttribType::Enum)itemType, normalized);
      }
      else if ( element.isSemantic( GFXSemantic::TANGENT ) )
      {
         Con::printf("[bgfx] Semantic: Tangent");
         decl->add(bgfx::Attrib::Tangent, itemCount, (bgfx::AttribType::Enum)itemType, normalized);
      }
      else if ( element.isSemantic( GFXSemantic::TANGENTW ) )
      {
         Con::printf("[bgfx] Semantic: TangentW");
         decl->add(bgfx::Attrib::Tangent, itemCount, (bgfx::AttribType::Enum)itemType, normalized);
      }
      else if ( element.isSemantic( GFXSemantic::BINORMAL ) )
      {
         Con::printf("[bgfx] Semantic: Binormal (Registering as Bitangent)");
         decl->add(bgfx::Attrib::Bitangent, itemCount, (bgfx::AttribType::Enum)itemType, normalized);
      }
      else
      {
         U32 idx = element.getSemanticIndex();
         Con::printf("[bgfx] Semantic: TexCoord %d", idx);
         decl->add((bgfx::Attrib::Enum)(bgfx::Attrib::TexCoord0 + idx), itemCount, (bgfx::AttribType::Enum)itemType);
      }
   }
   decl->end();

   Con::printf("[bgfx] Semantic: Layout END");

   // Cache and return.
   vertDecl = new BGFXVertexDecl();
   vertDecl->decl = decl;
   mVertexDecls[vertexFormat->getDescription()] = vertDecl;
   return vertDecl;
}

void GFXBGFXDevice::setVertexDecl( const GFXVertexDecl *decl )
{
   if ( !decl ) return;
   mVertexDecl = static_cast<const BGFXVertexDecl*>( decl )->decl;
}

void GFXBGFXDevice::setTextureInternal(U32 textureUnit, const GFXTextureObject* texture)
{
   const GFXBGFXTextureObject* tex = static_cast<const GFXBGFXTextureObject*>(texture);
   if ( !tex ) return;
   //bgfx::setTexture( 0, u_texColor, tex->mBGFXTexture );
   internalTex = tex->mBGFXTexture;
   //Con::printf("[BGFX] Changing Texture.");
}

void GFXBGFXDevice::drawPrimitive( GFXPrimitiveType primType, U32 vertexStart, U32 primitiveCount )
{
   // Stop GUI Rendering to do 3D Stuff.
   endNVGFrame();

   if( mStateDirty )
      updateStates();

   if ( mVertexBuffer != NULL )
      mVertexBuffer->setActive(vertexStart, mVertexBufferFreq * primitiveCount);

   if ( mShader && mShader->mShaderProgram.idx != bgfx::invalidHandle )
      bgfx::setProgram(mShader->mShaderProgram);

   if ( internalTex.idx != bgfx::invalidHandle )
      bgfx::setTexture( 0, u_texColor, internalTex, mTextureFlags );

   if ( worldMat && viewMat && projMat )
   {
      MatrixF* finalTransform = new MatrixF(worldMat);
      finalTransform->mulL(*viewMat);
      finalTransform->mulL(*projMat);
      bgfx::setTransform(finalTransform);
   } else if ( projMat )
   {
      bgfx::setTransform(*projMat);
   }

   U64 state = mState;

   if ( primType == GFXPrimitiveType::GFXTriangleStrip )
      state = state | BGFX_STATE_PT_TRISTRIP;

   if ( primType == GFXPrimitiveType::GFXTriangleFan )
      Con::printf("[BGFX] GFXPrimitiveType::GFXTriangleFan is deprecated.");

   if ( primType == GFXPrimitiveType::GFXLineList )
      state = state | BGFX_STATE_PT_LINES;

   if ( primType == GFXPrimitiveType::GFXPointList )
      state = state | BGFX_STATE_PT_POINTS;

   bgfx::setState(state);
   bgfx::submit(0);
   //Con::printf("[BGFX] Drawing Primitive.");
}

void GFXBGFXDevice::_setPrimitiveBuffer( GFXPrimitiveBuffer *buffer ) 
{
   mCurrentPB = static_cast<GFXBGFXPrimitiveBuffer *>( buffer );
}

void GFXBGFXDevice::drawIndexedPrimitive(  GFXPrimitiveType primType, 
                                       U32 startVertex, 
                                       U32 minIndex, 
                                       U32 numVerts, 
                                       U32 startIndex, 
                                       U32 primitiveCount ) 
{
   if ( mCurrentPB != NULL )
   {
      mCurrentPB->setActive(startVertex, 
                            minIndex, 
                            numVerts, 
                            startIndex, 
                            primitiveCount);
   }
   drawPrimitive(primType, startVertex, primitiveCount);
};

void GFXBGFXDevice::setMatrix( GFXMatrixType mtype, const MatrixF &mat )
{
   if ( mtype == GFXMatrixType::GFXMatrixProjection )
   {
      bgfx::setViewTransform(0, MatrixF::Identity, MatrixF::Identity);
      SAFE_DELETE(projMat);
      projMat = new MatrixF(mat);
   }
   if ( mtype == GFXMatrixType::GFXMatrixView )
   {
      delete viewMat;
      viewMat = new MatrixF(mat);
      //bgfx::setViewTransform(0, viewMat, projMat);
   }
   if ( mtype == GFXMatrixType::GFXMatrixWorld )
   {
      delete worldMat;
      worldMat = new MatrixF(mat);
   }
}

GFXShader* GFXBGFXDevice::createShader()
{
   GFXBGFXShader* shader = new GFXBGFXShader();
   return shader;
}

void GFXBGFXDevice::setupGenericShaders( GenericShaderType type )
{
   if( mGenericShader[GSColor] == NULL )
   {
      mGenericShader[GSColor] = createShader();
      mGenericShader[GSColor]->init("shaders/colorV.sc", "shaders/colorP.sc", 3.0, NULL);

      mGenericShader[GSAddColorTexture] = createShader();
      mGenericShader[GSAddColorTexture]->init("shaders/addColorTextureV.sc", "shaders/addColorTextureP.sc", 3.0, NULL);

      mGenericShader[GSModColorTexture] = createShader();
      mGenericShader[GSModColorTexture]->init("shaders/modColorTextureV.sc", "shaders/modColorTextureP.sc", 3.0, NULL);
   }

   setShader(mGenericShader[type]);
}

void GFXBGFXDevice::setClipRect( const RectI &inRect )
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

   RectI maxRect(Point2I(0,0), Point2I(size.x,size.y*10));
   rect.intersect(maxRect);

   mClipRect = rect;

   F32 l = F32( mClipRect.point.x );
   F32 r = F32( mClipRect.point.x + mClipRect.extent.x );
   F32 b = F32( mClipRect.point.y + mClipRect.extent.y );
   F32 t = F32( mClipRect.point.y );

   // Set up projection matrix.
   // The x and y of the screen go from -1 to 1, so 0,0 is center screen.
   // The values used below were worked out mathematically except for the
   // magic 0.999's that show up. They were originally worked out to 1.0 but 
   // the whole screen off by 1 pixel. Why? I don't know. Maybe it's a bug in 
   // bgfx maybe its a bug in my calculations. Either way, I tested the  
   // dimensions against stock torque and all the GUI comes out with proper 
   // pixel by pixel dimensions with no visual issues.
   //  - andrewmac
   static Point4F pt;   

   // Width, 0.0f, 0.0f, 0.0f
   pt.set(((( r - l ) / size.x) * 2.0f) / ( r - l ), 0.0f, 0.0f, 0.0f);
   mTempMatrix.setRow(0, pt);

   // 0.0f, -Height, 0.0f, 0.0f
   pt.set(0.0f, ((( t - b ) / size.y) * -2.0f) / ( t - b ), 0.0f, 0.0f);
   mTempMatrix.setRow(1, pt);

   // 0.0f, 0.0f, Depth?, 0.0f
   pt.set(0.0f, 0.0f, 16.0f, 0.0f);
   mTempMatrix.setRow(2, pt);

   F32 one_x_pix = 1.0 / size.x;
   F32 one_y_pix = 1.0 / size.y;

   // X, -Y, Z, 1.0f
   pt.set((-2.0 / size.x) - (1.0 - one_x_pix), (2.0 / size.y) + (1.0 - one_y_pix), 1.0f, 1.0f);
   mTempMatrix.setRow(3, pt);

   // Set Projection Matrix.
   setProjectionMatrix( mTempMatrix );

   // Set up world/view matrix
   mTempMatrix.identity();   
   setWorldMatrix( mTempMatrix );

   //setViewport( mClipRect );
}

void GFXBGFXDevice::createTestFont()
{
	fontManager = new FontManager(512);
	textBufferManager = new TextBufferManager(fontManager);

   if ( testFontFile.readMemory("fonts/droidsans.ttf") )
   {
      ttFontHandle = fontManager->createTtf((uint8_t*)testFontFile.buffer(), testFontFile.getBufferSize());
   }

   if ( ttFontHandle.idx != bgfx::invalidHandle )
   {
      Con::printf("FONT CREATED SUCCESSFULLY!");
      fontHandle = fontManager->createFontByPixelSize(ttFontHandle, 0, 32);
      fontManager->preloadGlyph(fontHandle, L"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. \n");

      textBuffer = textBufferManager->createTextBuffer(FONT_TYPE_ALPHA, BufferType::Static);
      if ( textBuffer.idx == bgfx::invalidHandle )
      {
         Con::printf("Could not create text buffer.");
         return;
      }

      textBufferManager->setTextColor(textBuffer, 0x000000FF);
      textBufferManager->setPenPosition(textBuffer, 10.0f, 10.0f);
      textBufferManager->setStyle(textBuffer, STYLE_NORMAL);
      textBufferManager->appendText(textBuffer, fontHandle, L"I really think this text just looks nice.\n");
      textBufferManager->appendText(textBuffer, fontHandle, L"Crisp, gorgeous.\n");
      textBufferManager->appendText(textBuffer, fontHandle, L"I don't know what else to put here.\n");
      textBufferManager->appendText(textBuffer, fontHandle, L"LALALALLALLL ALALLALALA LALALAALLA");
   }
}

void GFXBGFXDevice::setShader( GFXShader *shader )
{
   //Con::printf("[BGFX] Attempting to change shader.");
   if ( !shader ) return;

   mShader = static_cast<GFXBGFXShader*>( shader );
   //bgfxShader;

}

GFXDrawUtil* GFXBGFXDevice::getDrawUtil()
{
   if (!mDrawer)
   {
      mDrawer = new GFXBGFXDrawUtil(this);
   }
   return mDrawer;
}

// Stateblocks
void GFXBGFXDevice::setStateBlockInternal(GFXStateBlock* block, bool force)
{
   mStateBlock = static_cast<GFXBGFXStateBlock*>(block);
   mState = mStateBlock->getBGFXState();
   mTextureFlags = mStateBlock->getTextureFlags();
}

GFXTextureTarget * GFXBGFXDevice::allocRenderToTextureTarget()
{
   GFXBGFXTextureTarget *targ = new GFXBGFXTextureTarget();
   targ->registerResourceWithDevice(this);
   return targ;
}

// ------------ TEST CUBE ------------------------
void GFXBGFXDevice::initTestCube()
{
   PosColorVertex::init();

	// Create test cube static vertex buffer.
	testCubeVB = bgfx::createVertexBuffer(
		  // Static data can be passed with bgfx::makeRef
		  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
		, PosColorVertex::ms_decl
		);

	// Create test cube static index buffer.
	testCubeIB = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) )
		);
}

void GFXBGFXDevice::drawTestCube()
{


   float at[3] = { 0.0f, 0.0f, 0.0f };
	float eye[3] = { 0.0f, 0.0f, -35.0f };
   float view[16];
	float proj[16];
   Point2I size = mCurrentRT->getSize();
	bx::mtxLookAt(view, eye, at);
	bx::mtxProj(proj, 60.0f, float(size.x)/float(size.y), 0.1f, 100.0f);
   bgfx::setViewTransform(1, view, proj);
   bgfx::setViewRect(1, 0, 0, size.x, size.y);

   // Set vertex and fragment shaders.
   setupGenericShaders();
   if ( mShader && mShader->mShaderProgram.idx != bgfx::invalidHandle )
      bgfx::setProgram(mShader->mShaderProgram);

   float mtx[16];
	bx::mtxRotateXY(mtx,0.21f, 0.37f);
	mtx[12] = -15.0f;
	mtx[13] = -15.0f;
	mtx[14] = 0.0f;

	// Set model matrix for rendering.
	bgfx::setTransform(mtx);

	// Set vertex and index buffer.
	bgfx::setVertexBuffer(testCubeVB);
	bgfx::setIndexBuffer(testCubeIB);

	// Set render states.
	bgfx::setState(BGFX_STATE_DEFAULT);

	// Submit primitive for rendering to view 0.
	bgfx::submit(1);
}