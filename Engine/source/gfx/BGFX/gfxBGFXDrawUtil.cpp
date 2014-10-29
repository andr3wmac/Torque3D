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
#include "gfx/BGFX/GFXBGFXDrawUtil.h"

#include "gfx/gfxDevice.h"
#include "core/strings/stringFunctions.h"
#include "gfx/gfxCubemap.h"
#include "gfx/screenshot.h"
#include "gfx/gfxPrimitiveBuffer.h"
#include "gfx/gfxCardProfile.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/gfxStateBlock.h"
#include "gfx/bitmap/gBitmap.h"
#include "core/util/safeDelete.h"
#include "windowManager/win32/win32Window.h"
#include "core/strings/unicode.h"
#include "gfx/gFont.h"

#include <bgfx.h>
#include <bgfxplatform.h>

GFXBGFXDrawUtil::GFXBGFXDrawUtil(GFXDevice * d)
   : GFXDrawUtil(d)
{
   bgfxDevice = static_cast<GFXBGFXDevice*>(d);
}

GFXBGFXDrawUtil::~GFXBGFXDrawUtil()
{
   //
}

void GFXBGFXDrawUtil::drawRectFill( const Point2F &upperLeft, const Point2F &lowerRight, const ColorI &color )
{
   GFXDrawUtil::drawRectFill(upperLeft, lowerRight, color);
   return;

   NVGcontext* nvg = bgfxDevice->getNVGContext();

   nvgBeginPath(nvg);
	nvgRect(nvg, upperLeft.x, upperLeft.y, lowerRight.x - upperLeft.x, lowerRight.y - upperLeft.y);
	nvgFillColor(nvg, nvgRGBA(color.red, color.green, color.blue, color.alpha));
	nvgFill(nvg);
}

U32 GFXBGFXDrawUtil::drawTextN( GFont *font, const Point2I &ptDraw, const UTF16 *in_string, U32 n, const ColorI *colorTable, const U32 maxColorIndex, F32 rot )
{
   NVGcontext* nvgContext = bgfxDevice->getNVGContext();
   const char* text = convertUTF16toUTF8(in_string);

   U32 fontSize = font->getFontSize();
   nvgFontSize(nvgContext, fontSize);

   String faceName = font->getFontFaceName();
   //Con::printf("Font Face Name: %s", faceName.c_str());

   U32 fontID = nvgFindFont(nvgContext, faceName);
   if ( fontID < 0 )
      fontID = nvgFindFont(nvgContext, "sans");

	nvgFontFaceId(nvgContext, fontID);
   if ( !colorTable )
      nvgFillColor(nvgContext, nvgRGBA(0, 0, 0, 255));
   else
      nvgFillColor(nvgContext, nvgRGBA(colorTable[0].red, colorTable[0].green, colorTable[0].blue, colorTable[0].alpha));
      
   nvgTextAlign(nvgContext, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
	nvgText(nvgContext, ptDraw.x, ptDraw.y, text, NULL);

   return ptDraw.x;
}

void GFXBGFXDrawUtil::drawBitmapStretchSR( GFXTextureObject*texture, const RectF &dstRect, const RectF &srcRect, const GFXBitmapFlip in_flip, const GFXTextureFilterType filter , bool in_wrap )
{
   GFXDrawUtil::drawBitmapStretchSR(texture, dstRect, srcRect, in_flip, filter, in_wrap);
   // Do Nothing for Now.
}