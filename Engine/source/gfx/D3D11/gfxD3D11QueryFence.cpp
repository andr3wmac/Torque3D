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

#include "gfx/D3D11/gfxD3D11Device.h"
#include "gfx/D3D11/gfxD3D11QueryFence.h"

GFXD3D11QueryFence::~GFXD3D11QueryFence()
{
   SAFE_RELEASE(mQuery);
}

void GFXD3D11QueryFence::issue()
{
   PROFILE_START(GFXD3D11QueryFence_issue);

   // Create the query if we need to
   if(mQuery == NULL)
   {
	  D3D11_QUERY_DESC QueryDesc;
	  QueryDesc.Query = D3D11_QUERY_EVENT;
	  QueryDesc.MiscFlags = 0;

	  HRESULT hRes = D3D11DEVICE->CreateQuery(&QueryDesc, &mQuery);

	  if(FAILED(hRes))
	  {
		AssertFatal(false, "Hardware does not support D3D11 Queries, this should be caught before this fence type is created" );
	  }

      AssertISV(hRes != E_OUTOFMEMORY, "Out of memory");
   }

   // Issue the query
   D3D11DEVICECONTEXT->End(mQuery);
   PROFILE_END();
}

GFXFence::FenceStatus GFXD3D11QueryFence::getStatus() const
{
   if(mQuery == NULL)
      return GFXFence::Unset;

   HRESULT hRes = D3D11DEVICECONTEXT->GetData(mQuery, NULL, 0, 0);

   return (hRes == S_OK ? GFXFence::Processed : GFXFence::Pending);
}

void GFXD3D11QueryFence::block()
{
   PROFILE_SCOPE(GFXD3D11QueryFence_block);

   // Calling block() before issue() is valid, catch this case
   if( mQuery == NULL )
      return;

   HRESULT hRes;
   while((hRes = D3D11DEVICECONTEXT->GetData(mQuery, NULL, 0, 0)) == S_FALSE); //D3DGETDATA_FLUSH
}

void GFXD3D11QueryFence::zombify()
{
}

void GFXD3D11QueryFence::resurrect()
{
}

const String GFXD3D11QueryFence::describeSelf() const
{
   // We've got nothing
   return String();
}