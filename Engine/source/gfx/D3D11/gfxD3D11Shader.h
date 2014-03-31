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

#ifndef _GFXD3D11SHADER_H_
#define _GFXD3D11SHADER_H_

#include <d3dcompiler.h>

#include "core/util/path.h"
#include "core/util/tDictionary.h"
#include "gfx/gfxShader.h"
#include "gfx/gfxResource.h"
#include "gfx/genericConstBuffer.h"
#include "gfx/D3D11/gfxD3D11Device.h"

class GFXD3D11Shader;

enum CONST_CLASS
{
	D3DPC_SCALAR,
	D3DPC_VECTOR,
	D3DPC_MATRIX_ROWS,
	D3DPC_MATRIX_COLUMNS,
	D3DPC_OBJECT,
	D3DPC_STRUCT
};

enum CONST_TYPE 
{ 
    D3DPT_VOID, 
    D3DPT_BOOL, 
    D3DPT_INT, 
    D3DPT_FLOAT, 
    D3DPT_STRING, 
    D3DPT_TEXTURE, 
    D3DPT_TEXTURE1D, 
    D3DPT_TEXTURE2D, 
    D3DPT_TEXTURE3D, 
    D3DPT_TEXTURECUBE, 
    D3DPT_SAMPLER, 
    D3DPT_SAMPLER1D, 
    D3DPT_SAMPLER2D, 
    D3DPT_SAMPLER3D, 
    D3DPT_SAMPLERCUBE, 
    D3DPT_PIXELSHADER, 
    D3DPT_VERTEXSHADER, 
    D3DPT_PIXELFRAGMENT, 
    D3DPT_VERTEXFRAGMENT
};

enum REGISTER_TYPE
{
	D3DRS_BOOL,
	D3DRS_INT4,
	D3DRS_FLOAT4,
	D3DRS_SAMPLER
};

struct ConstantDesc
{
    String Name;
    int RegisterIndex;
    int RegisterCount;
    int Rows;
    int Columns;
    int Elements;
    int StructMembers;
    REGISTER_TYPE RegisterSet;
    CONST_CLASS Class;
    CONST_TYPE Type;
    size_t Bytes;
};

class ConstantTable
{
public:
  bool Create(const void* data);

  size_t GetConstantCount() const { return m_constants.size(); }
  const String& GetCreator() const { return m_creator; } 

  const ConstantDesc* GetConstantByIndex(size_t i) const { return &m_constants[i]; }
  const ConstantDesc* GetConstantByName(const String& name) const;

  void ClearConstants() { m_constants.clear(); }

private:
  Vector<ConstantDesc> m_constants;
  String m_creator;
};

// Structs
struct CTHeader
{
  U32 Size;
  U32 Creator;
  U32 Version;
  U32 Constants;
  U32 ConstantInfo;
  U32 Flags;
  U32 Target;
};

struct CTInfo
{
  U32 Name;
  U16 RegisterSet;
  U16 RegisterIndex;
  U16 RegisterCount;
  U16 Reserved;
  U32 TypeInfo;
  U32 DefaultValue;
};

struct CTType
{
  U16 Class;
  U16 Type;
  U16 Rows;
  U16 Columns;
  U16 Elements;
  U16 StructMembers;
  U32 StructMemberInfo;
};

// Shader instruction opcodes
const U32 SIO_COMMENT = 0x0000FFFE;
const U32 SIO_END = 0x0000FFFF;
const U32 SI_OPCODE_MASK = 0x0000FFFF;
const U32 SI_COMMENTSIZE_MASK = 0x7FFF0000;
const U32 CTAB_CONSTANT = 0x42415443;

// Member functions
inline bool ConstantTable::Create(const void* data)
{
  const U32* ptr = static_cast<const U32*>(data);
  while(*++ptr != SIO_END)
  {
    if((*ptr & SI_OPCODE_MASK) == SIO_COMMENT)
    {
      // Check for CTAB comment
      U32 comment_size = (*ptr & SI_COMMENTSIZE_MASK) >> 16;
      if(*(ptr+1) != CTAB_CONSTANT)
      {
        ptr += comment_size;
        continue;
      }

      // Read header
      const char* ctab = reinterpret_cast<const char*>(ptr+2);
      size_t ctab_size = (comment_size-1)*4;

      const CTHeader* header = reinterpret_cast<const CTHeader*>(ctab);
      if(ctab_size < sizeof(*header) || header->Size != sizeof(*header))
        return false;
      m_creator = ctab + header->Creator;

      // Read constants
      m_constants.reserve(header->Constants);
      const CTInfo* info = reinterpret_cast<const CTInfo*>(ctab + header->ConstantInfo);
      for(U32 i = 0; i < header->Constants; ++i)
      {
        const CTType* type = reinterpret_cast<const CTType*>(ctab + info[i].TypeInfo);

        // Fill struct
        ConstantDesc desc;
        desc.Name = ctab + info[i].Name;
        desc.RegisterSet = static_cast<REGISTER_TYPE>(info[i].RegisterSet);
        desc.RegisterIndex = info[i].RegisterIndex;
        desc.RegisterCount = info[i].RegisterCount;
        desc.Rows = type->Rows;
        desc.Class = static_cast<CONST_CLASS>(type->Class);
        desc.Type = static_cast<CONST_TYPE>(type->Type);
        desc.Columns = type->Columns;
        desc.Elements = type->Elements;
        desc.StructMembers = type->StructMembers;
        desc.Bytes = 4 * desc.Elements * desc.Rows * desc.Columns;
        m_constants.push_back(desc);
      }
      return true;
    }
  }
  return false;
}

inline const ConstantDesc* ConstantTable::GetConstantByName(const String& name) const
{
  Vector<ConstantDesc>::const_iterator it;
  for(it = m_constants.begin(); it != m_constants.end(); ++it)
  {
    if(it->Name == name)
      return &(*it);
  }
  return NULL;
}

class GFXD3D11ShaderBufferLayout : public GenericConstBufferLayout
{
protected:
   /// Set a matrix, given a base pointer
   virtual bool setMatrix(const ParamDesc& pd, const GFXShaderConstType constType, const U32 size, const void* data, U8* basePointer);
};

class GFXD3D11ShaderConstHandle : public GFXShaderConstHandle
{
public:   

   // GFXShaderConstHandle
   const String& getName() const;
   GFXShaderConstType getType() const;
   U32 getArraySize() const;

   WeakRefPtr<GFXD3D11Shader> mShader;

   bool mVertexConstant;
   GenericConstBufferLayout::ParamDesc mVertexHandle;
   bool mPixelConstant;
   GenericConstBufferLayout::ParamDesc mPixelHandle;
   
   /// Is true if this constant is for hardware mesh instancing.
   ///
   /// Note: We currently store its settings in mPixelHandle.
   ///
   bool mInstancingConstant;

   void setValid( bool valid ) { mValid = valid; }
   S32 getSamplerRegister() const;

   // Returns true if this is a handle to a sampler register.
   bool isSampler() const 
   {
      return ( mPixelConstant && mPixelHandle.constType >= GFXSCT_Sampler ) || ( mVertexConstant && mVertexHandle.constType >= GFXSCT_Sampler );
   }

   /// Restore to uninitialized state.
   void clear()
   {
      mShader = NULL;
      mVertexConstant = false;
      mPixelConstant = false;
      mInstancingConstant = false;
      mVertexHandle.clear();
      mPixelHandle.clear();
      mValid = false;
   }

   GFXD3D11ShaderConstHandle();
};

class gfxD3D11Include : public ID3DInclude, public StrongRefBase
{
private:

    Vector<String> mLastPath;

public:

    void setPath( const String &path )
    {
       mLastPath.clear();
       mLastPath.push_back( path );
    }

    gfxD3D11Include() {}
    virtual ~gfxD3D11Include() {}

	STDMETHOD(Open)(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes);
	STDMETHOD(Close)(THIS_ LPCVOID pData);
};

typedef StrongRefPtr<gfxD3D11Include> gfxD3DIncludeRef;

class GFXD3D11Shader : public GFXShader
{
   friend class GFXD3D11Device;
   friend class GFXD3D11ShaderConstBuffer;

public:
   typedef Map<String, GFXD3D11ShaderConstHandle*> HandleMap;

   GFXD3D11Shader();
   virtual ~GFXD3D11Shader();   

   // GFXShader
   virtual GFXShaderConstBufferRef allocConstBuffer();
   virtual const Vector<GFXShaderConstDesc>& getShaderConstDesc() const;
   virtual GFXShaderConstHandle* getShaderConstHandle(const String& name); 
   virtual GFXShaderConstHandle* findShaderConstHandle(const String& name);
   virtual U32 getAlignmentValue(const GFXShaderConstType constType) const;
   virtual bool getDisassembly( String &outStr ) const;

   // GFXResource
   virtual void zombify();
   virtual void resurrect();

protected:

   virtual bool _init();   

   static const U32 smCompiledShaderTag;

   ConstantTable table;

   ID3D11VertexShader *mVertShader;
   ID3D11PixelShader *mPixShader;

   GFXD3D11ShaderBufferLayout* mVertexConstBufferLayoutF;   
   GFXD3D11ShaderBufferLayout* mPixelConstBufferLayoutF;
   GFXD3D11ShaderBufferLayout* mVertexConstBufferLayoutI;   
   GFXD3D11ShaderBufferLayout* mPixelConstBufferLayoutI;

   static gfxD3DIncludeRef smD3DInclude;

   HandleMap mHandles;

   /// The shader disassembly from DX when this shader is compiled.
   /// We only store this data in non-release builds.
   String mDissasembly;

   /// Vector of sampler type descriptions consolidated from _compileShader.
   Vector<GFXShaderConstDesc> mSamplerDescriptions;

   /// Vector of descriptions (consolidated for the getShaderConstDesc call)
   Vector<GFXShaderConstDesc> mShaderConsts;
   
   // These two functions are used when compiling shaders from hlsl
   virtual bool _compileShader( const Torque::Path &filePath, 
                                const String &target, 
                                const D3D_SHADER_MACRO *defines, 
                                GenericConstBufferLayout *bufferLayoutF, 
                                GenericConstBufferLayout *bufferLayoutI,
                                Vector<GFXShaderConstDesc> &samplerDescriptions );

   void _getShaderConstants( GenericConstBufferLayout *bufferLayoutF, 
                             GenericConstBufferLayout *bufferLayoutI,
                             Vector<GFXShaderConstDesc> &samplerDescriptions );

   bool _saveCompiledOutput( const Torque::Path &filePath, 
                             ID3DBlob *buffer, 
                             GenericConstBufferLayout *bufferLayoutF, 
                             GenericConstBufferLayout *bufferLayoutI,
                             Vector<GFXShaderConstDesc> &samplerDescriptions );

   // Loads precompiled shaders
   bool _loadCompiledOutput( const Torque::Path &filePath, 
                             const String &target, 
                             GenericConstBufferLayout *bufferLayoutF, 
                             GenericConstBufferLayout *bufferLayoutI,
                             Vector<GFXShaderConstDesc> &samplerDescriptions );

   // This is used in both cases
   virtual void _buildShaderConstantHandles( GenericConstBufferLayout *layout, bool vertexConst );
   
   virtual void _buildSamplerShaderConstantHandles( Vector<GFXShaderConstDesc> &samplerDescriptions );

   /// Used to build the instancing shader constants from 
   /// the instancing vertex format.
   void _buildInstancingShaderConstantHandles();
};

inline bool GFXD3D11Shader::getDisassembly( String &outStr ) const
{
   outStr = mDissasembly;
   return ( outStr.isNotEmpty() );
}

/// The D3D11 implementation of a shader constant buffer.
class GFXD3D11ShaderConstBuffer : public GFXShaderConstBuffer
{
   friend class GFXD3D11Shader;

public:

   GFXD3D11ShaderConstBuffer( GFXD3D11Shader* shader,
                             GFXD3D11ShaderBufferLayout* vertexLayoutF, 
                             GFXD3D11ShaderBufferLayout* vertexLayoutI,
                             GFXD3D11ShaderBufferLayout* pixelLayoutF, 
                             GFXD3D11ShaderBufferLayout* pixelLayoutI );
   virtual ~GFXD3D11ShaderConstBuffer();   

   /// Called by GFXD3D11Device to activate this buffer.
   /// @param mPrevShaderBuffer The previously active buffer
   void activate( GFXD3D11ShaderConstBuffer *prevShaderBuffer );
   
   /// Used internally by GXD3D11ShaderConstBuffer to determine if it's dirty.
   bool isDirty();

   /// Called from GFXD3D11Shader when constants have changed and need
   /// to be the shader this buffer references is reloaded.
   void onShaderReload( GFXD3D11Shader *shader );

   // GFXShaderConstBuffer
   virtual GFXShader* getShader();
   virtual void set(GFXShaderConstHandle* handle, const F32 fv);
   virtual void set(GFXShaderConstHandle* handle, const Point2F& fv);
   virtual void set(GFXShaderConstHandle* handle, const Point3F& fv);
   virtual void set(GFXShaderConstHandle* handle, const Point4F& fv);
   virtual void set(GFXShaderConstHandle* handle, const PlaneF& fv);
   virtual void set(GFXShaderConstHandle* handle, const ColorF& fv);   
   virtual void set(GFXShaderConstHandle* handle, const S32 f);
   virtual void set(GFXShaderConstHandle* handle, const Point2I& fv);
   virtual void set(GFXShaderConstHandle* handle, const Point3I& fv);
   virtual void set(GFXShaderConstHandle* handle, const Point4I& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<F32>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point2F>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point3F>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point4F>& fv);   
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<S32>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point2I>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point3I>& fv);
   virtual void set(GFXShaderConstHandle* handle, const AlignedArray<Point4I>& fv);
   virtual void set(GFXShaderConstHandle* handle, const MatrixF& mat, const GFXShaderConstType matType = GFXSCT_Float4x4);
   virtual void set(GFXShaderConstHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType = GFXSCT_Float4x4);
   
   // GFXResource
   virtual const String describeSelf() const;
   virtual void zombify();
   virtual void resurrect();

protected:

   template<class T>
   inline void SET_CONSTANT(  GFXShaderConstHandle* handle, 
                              const T& fv, 
                              GenericConstBuffer *vBuffer, 
                              GenericConstBuffer *pBuffer );

   // constant buffer
   ID3D11Buffer* mConstantBuffersVF;
   ID3D11Buffer* mConstantBuffersVI;
   ID3D11Buffer* mConstantBuffersPF;
   ID3D11Buffer* mConstantBuffersPI;

   /// We keep a weak reference to the shader 
   /// because it will often be deleted.
   WeakRefPtr<GFXD3D11Shader> mShader;
   
   GFXD3D11ShaderBufferLayout* mVertexConstBufferLayoutF;
   GenericConstBuffer* mVertexConstBufferF;
   GFXD3D11ShaderBufferLayout* mPixelConstBufferLayoutF;
   GenericConstBuffer* mPixelConstBufferF;   
   GFXD3D11ShaderBufferLayout* mVertexConstBufferLayoutI;
   GenericConstBuffer* mVertexConstBufferI;
   GFXD3D11ShaderBufferLayout* mPixelConstBufferLayoutI;
   GenericConstBuffer* mPixelConstBufferI;   
};

#endif
