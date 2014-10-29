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

#ifndef _GFXBGFXDrawUtil_H_
#define _GFXBGFXDrawUtil_H_

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
#ifndef _GFX_GFXDRAWER_H_
#include "gfx/gfxDrawUtil.h"
#endif
#ifndef _GFXBGFXDevice_H_
#include "gfx/BGFX/gfxBGFXDevice.h"
#endif
#ifndef NANOVG_H
#include <nanovg.h>
#endif

/// The BGFX implementation of a shader.
class GFXBGFXDrawUtil : public GFXDrawUtil
{
private:
   GFXBGFXDevice* bgfxDevice;

public:
   GFXBGFXDrawUtil(GFXDevice * d);
   ~GFXBGFXDrawUtil();

   virtual void drawRectFill( const Point2F &upperLeft, const Point2F &lowerRight, const ColorI &color );
   virtual U32 drawTextN( GFont *font, const Point2I &ptDraw, const UTF16 *in_string, U32 n, const ColorI *colorTable = NULL, const U32 maxColorIndex = 9, F32 rot = 0.f );
   virtual void drawBitmapStretchSR( GFXTextureObject*texture, const RectF &dstRect, const RectF &srcRect, const GFXBitmapFlip in_flip = GFXBitmapFlip_None, const GFXTextureFilterType filter = GFXTextureFilterPoint , bool in_wrap = true );
};

#endif // _GFXBGFXDrawUtil_H_