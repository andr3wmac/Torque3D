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

#ifndef _GFXBGFXDevice_H_
#define _GFXBGFXDevice_H_

#include "platform/platform.h"

//-----------------------------------------------------------------------------

#include "gfx/gfxDevice.h"
#include "gfx/gfxInit.h"
#include "gfx/gfxFence.h"
#include "windowManager/platformWindowMgr.h"

#ifndef _FILEOBJECT_H_
#include "core/fileObject.h"
#endif

#ifndef FONT_MANAGER_H_HEADER_GUARD
#include <font/font_manager.h>
#endif

#ifndef TEXT_BUFFER_MANAGER_H_HEADER_GUARD
#include <font/text_buffer_manager.h>
#endif

#ifndef _GFXBGFXSHADER_H_
#include "gfx/BGFX/gfxBGFXShader.h"
#endif

#ifndef _GFXBGFXStateBlock_H_
#include "gfx/BGFX/gfxBGFXStateBlock.h"
#endif

#ifndef _GFXBGFXVertexBuffer_H_
#include "gfx/BGFX/gfxBGFXVertexBuffer.h"
#endif

#ifndef _GFXBGFXPrimitiveBuffer_H_
#include "gfx/BGFX/gfxBGFXPrimitiveBuffer.h"
#endif

#ifndef BGFX_H_HEADER_GUARD
#include <bgfx.h>
#endif

#ifndef NANOVG_H
#include <nanovg.h>
#endif

// Little helper to convert colors.
#define BGFXCOLOR_RGBA(r,g,b,a) \
   ((U32)((((r)&0xff)<<24)|(((g)&0xff)<<16)|(((b)&0xff)<<8)|((a)&0xff)))



class GFXBGFXWindowTarget : public GFXWindowTarget
{
public:
   GFXBGFXWindowTarget(PlatformWindow* win)
      : GFXWindowTarget()
   {
      mWindow = win;
   }

   virtual bool present()
   {
      return true;
   }

   virtual const Point2I getSize()
   {
      return mWindow->getVideoMode().resolution; 
   }

   virtual GFXFormat getFormat() { return GFXFormatR8G8B8A8; }

   virtual void resetMode()
   {

   }

   virtual void zombify() {};
   virtual void resurrect() {};

};

class GFXBGFXDevice : public GFXDevice
{
public:
   class BGFXVertexDecl : public GFXVertexDecl
   {
   public:
      virtual ~BGFXVertexDecl()
      {
         //bgfx::de
      }

      bgfx::VertexDecl* decl;
   };

   GFXBGFXDevice();
   virtual ~GFXBGFXDevice();

   static GFXDevice *createInstance( U32 adapterIndex );

   static void enumerateAdapters( Vector<GFXAdapter*> &adapterList );

   void init( const GFXVideoMode &mode, PlatformWindow *window = NULL );

   virtual void activate() { };
   virtual void deactivate() { };
   virtual GFXAdapterType getAdapterType() { return BGFXDevice; };

   /// @name Debug Methods
   /// @{
   virtual void enterDebugEvent(ColorI color, const char *name) { };
   virtual void leaveDebugEvent() { };
   virtual void setDebugMarker(ColorI color, const char *name) { };
   /// @}

   /// Enumerates the supported video modes of the device
   virtual void enumerateVideoModes() { };

   /// Sets the video mode for the device
   virtual void setVideoMode( const GFXVideoMode &mode );
protected:
   static GFXAdapter::CreateDeviceInstanceDelegate mCreateDeviceInstance; 

   /// Called by GFXDevice to create a device specific stateblock
   virtual GFXStateBlockRef createStateBlockInternal(const GFXStateBlockDesc& desc);
   /// Called by GFXDevice to actually set a stateblock.
   virtual void setStateBlockInternal(GFXStateBlock* block, bool force);
   /// @}

   /// Called by base GFXDevice to actually set a const buffer
   virtual void setShaderConstBufferInternal(GFXShaderConstBuffer* buffer) { };

   virtual void setTextureInternal(U32 textureUnit, const GFXTextureObject*texture);

   virtual void setLightInternal(U32 lightStage, const GFXLightInfo light, bool lightEnable);
   virtual void setLightMaterialInternal(const GFXLightMaterial mat) { };
   virtual void setGlobalAmbientInternal(ColorF color) { };

   /// @name State Initalization.
   /// @{

   /// State initalization. This MUST BE CALLED in setVideoMode after the device
   /// is created.
   virtual void initStates() { };

   virtual void setMatrix( GFXMatrixType mtype, const MatrixF &mat );

   virtual GFXVertexBuffer *allocVertexBuffer(  U32 numVerts, 
                                                const GFXVertexFormat *vertexFormat, 
                                                U32 vertSize, 
                                                GFXBufferType bufferType );
   virtual GFXPrimitiveBuffer *allocPrimitiveBuffer(  U32 numIndices, 
                                                      U32 numPrimitives, 
                                                      GFXBufferType bufferType );

   /// Used to lookup a vertex declaration for the vertex format.
   /// @see allocVertexDecl
   typedef Map<String, BGFXVertexDecl*> VertexDeclMap;
   VertexDeclMap mVertexDecls;

   virtual GFXVertexDecl* allocVertexDecl( const GFXVertexFormat *vertexFormat );
   virtual void setVertexDecl( const GFXVertexDecl *decl );
   virtual void setVertexStream( U32 stream, GFXVertexBuffer *buffer );
   virtual void setVertexStreamFrequency( U32 stream, U32 frequency );

public:
   virtual GFXCubemap * createCubemap();

   virtual F32 getFillConventionOffset() const { return 0.0f; };

   ///@}

   virtual GFXTextureTarget *allocRenderToTextureTarget();
   virtual GFXWindowTarget *allocWindowTarget(PlatformWindow *window);

   virtual void _updateRenderTargets(){};

   virtual F32 getPixelShaderVersion() const { return 5.0f; };
   virtual void setPixelShaderVersion( F32 version ) { };
   virtual U32 getNumSamplers() const { return 16; };
   virtual U32 getNumRenderTargets() const { return 4; };

   virtual GFXShader* createShader();
   virtual void setShader( GFXShader *shader );

   virtual void clear( U32 flags, ColorI color, F32 z, U32 stencil );
   virtual bool beginSceneInternal();
   virtual void endSceneInternal();

   GFXBGFXPrimitiveBuffer* mCurrentPB;
   void _setPrimitiveBuffer( GFXPrimitiveBuffer *buffer );
   virtual void drawPrimitive( GFXPrimitiveType primType, U32 vertexStart, U32 primitiveCount );
   virtual void drawIndexedPrimitive(  GFXPrimitiveType primType, 
                                       U32 startVertex, 
                                       U32 minIndex, 
                                       U32 numVerts, 
                                       U32 startIndex, 
                                       U32 primitiveCount );

   virtual void setClipRect( const RectI &rect );
   virtual const RectI &getClipRect() const { return clip; };

   virtual void preDestroy() { Parent::preDestroy(); };

   virtual U32 getMaxDynamicVerts() { return 16384; };
   virtual U32 getMaxDynamicIndices() { return 16384; };

   GFXShaderRef mGenericShader[GS_COUNT];
   virtual GFXShaderRef getGenericShader( GenericShaderType type = GSColor ) { return mGenericShader[type]; };
   virtual void setupGenericShaders( GenericShaderType type = GSColor );

   virtual GFXFormat selectSupportedFormat(  GFXTextureProfile *profile, 
                                             const Vector<GFXFormat> &formats, 
                                             bool texture, 
                                             bool mustblend, 
                                             bool mustfilter ) { return GFXFormatR8G8B8A8; };

   GFXFence *createFence() { return new GFXGeneralFence( this ); }
   GFXOcclusionQuery* createOcclusionQuery() { return NULL; }
   
   // Current Vertex Buffer State
   bgfx::VertexDecl* mVertexDecl;

   virtual GFXDrawUtil *getDrawUtil();

private:
   typedef GFXDevice Parent;
   RectI clip;
   U32 mWindowWidth;
   U32 mWindowHeight;
   U32 testCounter;
   PlatformWindow* mWindow;

   MatrixF* worldMat;
   MatrixF* viewMat;
   MatrixF* projMat;
   MatrixF  mTempMatrix;    ///< Temporary matrix, no assurances on value at all
   RectI    mClipRect;

   // Previous Clear State
   U8 prevFlags;
   U32 prevColor;
   F32 prevZ;

   bgfx::UniformHandle u_texColor;
   bgfx::TextureHandle internalTex;

   FontManager* fontManager;
   TextBufferManager* textBufferManager;
   TextBufferHandle textBuffer;
   void createTestFont();
   FileObject testFontFile;
   TrueTypeHandle ttFontHandle;
   FontHandle fontHandle;

   U32 currentView;
   S32 nvgFont;
   NVGcontext* nvgContext;
   void drawNGV();
   bool nvgInFrame;

   U64 mTextureFlags;
   U64 mState;
   GFXBGFXStateBlock* mStateBlock;
   GFXBGFXVertexBuffer* mVertexBuffer;
   U32 mVertexBufferFreq;
   GFXBGFXShader* mShader;

public:
   NVGcontext* getNVGContext();
   void endNVGFrame();

   // Test Cube
   bgfx::VertexBufferHandle testCubeVB;
   bgfx::IndexBufferHandle testCubeIB;
   void initTestCube();
   void drawTestCube();
};

#endif
