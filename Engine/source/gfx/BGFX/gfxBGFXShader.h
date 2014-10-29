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

#ifndef _GFXBGFXSHADER_H_
#define _GFXBGFXSHADER_H_

#ifndef _PATH_H_
#include "core/util/path.h"
#endif
#ifndef _GFXSHADER_H_
#include "gfx/gfxShader.h"
#endif
#ifndef _GFXRESOURCE_H_
#include "gfx/gfxResource.h"
#endif
#ifndef _GENERICCONSTBUFFER_H_
#include "gfx/genericConstBuffer.h"
#endif
#ifndef _FILEOBJECT_H_
#include "core/fileObject.h"
#endif
#ifndef BGFX_H_HEADER_GUARD
#include <bgfx.h>
#endif

/// The BGFX implementation of a shader.
class GFXBGFXShader : public GFXShader
{
public:
   FileObject*          mVertexShaderFile;
   FileObject*          mPixelShaderFile;
   bgfx::ShaderHandle   mVertexShader;
   bgfx::ShaderHandle   mPixelShader;
   bgfx::ProgramHandle  mShaderProgram;

   GFXBGFXShader();
   virtual ~GFXBGFXShader();   

   // GFXShader
   virtual GFXShaderConstBufferRef allocConstBuffer() { return NULL; }  
   virtual const Vector<GFXShaderConstDesc>& getShaderConstDesc() const { return NULL; } 
   virtual GFXShaderConstHandle* getShaderConstHandle( const String& name ) { return NULL; }
   virtual U32 getAlignmentValue(const GFXShaderConstType constType) const { return 0; } 
   virtual bool getDisassembly( String &outStr ) const { return false; }

   virtual void zombify() {}
   virtual void resurrect() {}

protected:
   virtual bool _init();   
};

#endif // _GFXBGFXSHADER_H_