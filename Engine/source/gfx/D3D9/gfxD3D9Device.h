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

#ifndef _GFXD3D9DEVICE_H_
#define _GFXD3D9DEVICE_H_

#include <d3d9.h>

#include "platform/tmm_off.h"
#include "platformWin32/platformWin32.h"
#include "gfx/D3D9/gfxD3D9Shader.h"
#include "gfx/D3D9/gfxD3D9StateBlock.h"
#include "gfx/D3D9/gfxD3D9TextureManager.h"
#include "gfx/D3D9/gfxD3D9Cubemap.h"
#include "gfx/D3D9/gfxD3D9IndexBuffer.h"
#include "gfx/D3D9/gfxD3D9VideoCapture.h"
#include "gfx/gfxInit.h"
#include "gfx/gfxResource.h"
#include "platform/tmm_on.h"

#define D3D9DEVICE static_cast<GFXD3D9Device*>(GFX)->getDevice()

class PlatformWindow;
class GFXD3D9ShaderConstBuffer;

//------------------------------------------------------------------------------

class GFXD3D9Device : public GFXDevice
{
   friend class GFXResource;
   friend class GFXD3D9PrimitiveBuffer;
   friend class GFXD3D9VertexBuffer;
   friend class GFXD3D9TextureObject;
   friend class GFXD3D9TextureTarget;
   friend class GFXD3D9WindowTarget;

   virtual GFXFormat selectSupportedFormat(GFXTextureProfile *profile,
   const Vector<GFXFormat> &formats, bool texture, bool mustblend, bool mustfilter);

   virtual void enumerateVideoModes();

   virtual GFXWindowTarget *allocWindowTarget(PlatformWindow *window);
   virtual GFXTextureTarget *allocRenderToTextureTarget();

   virtual void enterDebugEvent(ColorI color, const char *name){};
   virtual void leaveDebugEvent(){};
   virtual void setDebugMarker(ColorI color, const char *name){};

protected:

   virtual void initStates() { };
   GFXD3D9VideoFrameGrabber* mVideoFrameGrabber;

   static GFXAdapter::CreateDeviceInstanceDelegate mCreateDeviceInstance;

   void _validateMultisampleParams(D3DFORMAT format, D3DMULTISAMPLE_TYPE & aatype, DWORD & aalevel) const;

   MatrixF mTempMatrix;    ///< Temporary matrix, no assurances on value at all
   RectI mClipRect;

   typedef StrongRefPtr<GFXD3D9VertexBuffer> RPGDVB;
   Vector<RPGDVB> mVolatileVBList;

   class D3D9VertexDecl : public GFXVertexDecl
   {
   public:
      virtual ~D3D9VertexDecl()
      {
         SAFE_RELEASE( decl );
      }

      IDirect3DVertexDeclaration9 *decl;
   };

   /// Used to lookup a vertex declaration for the vertex format.
   /// @see allocVertexDecl
   typedef Map<String,D3D9VertexDecl*> VertexDeclMap;
   VertexDeclMap mVertexDecls;

   IDirect3DSurface9 *mDeviceBackbuffer;
   IDirect3DSurface9 *mDeviceDepthStencil;
   IDirect3DSurface9 *mDeviceColor;

   /// The stream 0 vertex buffer used for volatile VB offseting.
   GFXD3D9VertexBuffer *mVolatileVB;

   //-----------------------------------------------------------------------
   StrongRefPtr<GFXD3D9PrimitiveBuffer> mDynamicPB;                       ///< Dynamic index buffer
   GFXD3D9PrimitiveBuffer *mCurrentPB;

   IDirect3DVertexShader9 *mLastVertShader;
   IDirect3DPixelShader9 *mLastPixShader;

   S32 mCreateFenceType;

   LPDIRECT3D9EX       mD3D;
   LPDIRECT3DDEVICE9EX mD3DDevice;

   GFXShader* mCurrentShader;
   GFXShaderRef mGenericShader[GS_COUNT];
   GFXShaderConstBufferRef mGenericShaderBuffer[GS_COUNT];
   GFXShaderConstHandle *mModelViewProjSC[GS_COUNT];

   U32  mAdapterIndex;

   F32 mPixVersion;
   U32 mNumRenderTargets;

   D3DMULTISAMPLE_TYPE mMultisampleType;
   DWORD mMultisampleLevel;

   bool mOcclusionQuerySupported;

   /// The current adapter display mode.
   D3DDISPLAYMODEEX mDisplayMode;

   /// The current adapter display rotation.
   D3DDISPLAYROTATION mDisplayRotation;

   /// To manage creating and re-creating of these when device is aquired
   void reacquireDefaultPoolResources();

   /// To release all resources we control from D3DPOOL_DEFAULT
   void releaseDefaultPoolResources();

   virtual GFXD3D9VertexBuffer* findVBPool( const GFXVertexFormat *vertexFormat, U32 numVertsNeeded );
   virtual GFXD3D9VertexBuffer* createVBPool( const GFXVertexFormat *vertexFormat, U32 vertSize );

   // State overrides
   // {

   ///
   virtual void setTextureInternal(U32 textureUnit, const GFXTextureObject* texture);

   /// Called by GFXDevice to create a device specific stateblock
   virtual GFXStateBlockRef createStateBlockInternal(const GFXStateBlockDesc& desc);
   /// Called by GFXDevice to actually set a stateblock.
   virtual void setStateBlockInternal(GFXStateBlock* block, bool force);

   /// Track the last const buffer we've used.  Used to notify new constant buffers that
   /// they should send all of their constants up
   StrongRefPtr<GFXD3D9ShaderConstBuffer> mCurrentConstBuffer;
   /// Called by base GFXDevice to actually set a const buffer
   virtual void setShaderConstBufferInternal(GFXShaderConstBuffer* buffer);

   virtual void setMatrix( GFXMatrixType /*mtype*/, const MatrixF &/*mat*/ ) { };
   virtual void setLightInternal(U32 /*lightStage*/, const GFXLightInfo /*light*/, bool /*lightEnable*/) { };
   virtual void setLightMaterialInternal(const GFXLightMaterial /*mat*/) { };
   virtual void setGlobalAmbientInternal(ColorF /*color*/) { };

   // }

   // Index buffer management
   // {
   virtual void _setPrimitiveBuffer( GFXPrimitiveBuffer *buffer );
   virtual void drawIndexedPrimitive(  GFXPrimitiveType primType, 
                                       U32 startVertex, 
                                       U32 minIndex, 
                                       U32 numVerts, 
                                       U32 startIndex, 
                                       U32 primitiveCount );
   // }

   virtual GFXShader* createShader();

   /// Device helper function
   virtual D3DPRESENT_PARAMETERS setupPresentParams( const GFXVideoMode &mode, const HWND &hwnd ) const;
   
public:

   static bool IsWin7OrLater() // anis -> from microsoft example
   {
		OSVERSIONINFO version;
		ZeroMemory(&version, sizeof(version));
		version.dwOSVersionInfoSize = sizeof(version);
		GetVersionEx(&version);

		// Sample would run only on Win7 or higher
		// Flip Model present and its associated present statistics behavior are only available on Windows 7 or higher OS
		return (version.dwMajorVersion > 6) || ((version.dwMajorVersion == 6) && (version.dwMinorVersion >= 1));
   }

   static GFXDevice *createInstance( U32 adapterIndex );

   static void enumerateAdapters( Vector<GFXAdapter*> &adapterList );

   GFXTextureObject* createRenderSurface( U32 width, U32 height, GFXFormat format, U32 mipLevel );

   const D3DDISPLAYMODEEX& getDisplayMode() const { return mDisplayMode; }

   /// Constructor
   /// @param   d3d   Direct3D object to instantiate this device with
   /// @param   index   Adapter index since D3D can use multiple graphics adapters
   GFXD3D9Device(LPDIRECT3D9EX d3d, U32 index);
   virtual ~GFXD3D9Device();

   // Activate/deactivate
   // {
   virtual void init( const GFXVideoMode &mode, PlatformWindow *window = NULL );

   virtual void preDestroy() { GFXDevice::preDestroy(); if(mTextureManager) mTextureManager->kill(); }

   GFXAdapterType getAdapterType(){ return Direct3D9; }

   U32 getAdaterIndex() const { return mAdapterIndex; }

   virtual GFXCubemap *createCubemap();

   virtual F32  getPixelShaderVersion() const { return mPixVersion; }
   virtual void setPixelShaderVersion( F32 version ){ mPixVersion = version;} 

   virtual void setShader( GFXShader *shader );
   virtual U32  getNumSamplers() const { return 16; }
   virtual U32  getNumRenderTargets() const { return mNumRenderTargets; }
   // }

   // Misc rendering control
   // {
   virtual void clear( U32 flags, ColorI color, F32 z, U32 stencil );
   virtual bool beginSceneInternal();
   virtual void endSceneInternal();

   virtual void setClipRect( const RectI &rect );
   virtual const RectI& getClipRect() const { return mClipRect; }

   // }

   /// @name Render Targets
   /// @{
   virtual void _updateRenderTargets();
   /// @}

   // Vertex/Index buffer management
   // {
   virtual GFXVertexBuffer* allocVertexBuffer(  U32 numVerts, 
                                                const GFXVertexFormat *vertexFormat,
                                                U32 vertSize,
                                                GFXBufferType bufferType );
   virtual GFXPrimitiveBuffer *allocPrimitiveBuffer(  U32 numIndices, 
                                                      U32 numPrimitives, 
                                                      GFXBufferType bufferType );

   virtual GFXVertexDecl* allocVertexDecl( const GFXVertexFormat *vertexFormat );
   virtual void setVertexDecl( const GFXVertexDecl *decl );

   virtual void setVertexStream( U32 stream, GFXVertexBuffer *buffer );
   virtual void setVertexStreamFrequency( U32 stream, U32 frequency );

   // }

   virtual U32 getMaxDynamicVerts() { return MAX_DYNAMIC_VERTS; }
   virtual U32 getMaxDynamicIndices() { return MAX_DYNAMIC_INDICES; }

   // Rendering
   // {
   virtual void drawPrimitive( GFXPrimitiveType primType, U32 vertexStart, U32 primitiveCount );
   // }

   LPDIRECT3DDEVICE9EX getDevice(){ return mD3DDevice; }
   LPDIRECT3D9EX getD3D() { return mD3D; }

   /// Reset
   void reset(D3DPRESENT_PARAMETERS &d3dpp);

   virtual void setupGenericShaders( GenericShaderType type  = GSColor );

   inline virtual F32 getFillConventionOffset() const { return 0.5f; }
   virtual void doParanoidStateCheck() {};

   GFXFence *createFence();

   GFXOcclusionQuery* createOcclusionQuery();   

   // Default multisample parameters
   D3DMULTISAMPLE_TYPE getMultisampleType() const { return mMultisampleType; }
   DWORD getMultisampleLevel() const { return mMultisampleLevel; }
};

#endif
