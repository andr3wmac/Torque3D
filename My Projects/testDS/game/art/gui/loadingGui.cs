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

//------------------------------------------------------------------------------
function LoadingGui::onWake(%this)
{
   // If the Disconnect button doesn't exist, add it.  We need to do this here
   // as the LoadingGui is a core GUI that we (GarageGames) don't want to change.
   // However, feel free to change core GUI's for your own game.
   if ( !isObject( %this-->DisconnectButton ) )
   {
      %extent = %this.getExtent();
      %width = getWord( %extent, 0 );
      %height = getWord( %extent, 1 );
      
      %button = new GuiBitmapButtonCtrl() {
         bitmap = "art/gui/Buttons/Button_Disconnect";
         bitmapMode = "Stretched";
         autoFitExtents = "0";
         useModifiers = "0";
         useStates = "1";
         groupNum = "-1";
         buttonType = "PushButton";
         useMouseEvents = "0";
         position = (%width - 314) @ " " @ (%height - 87); // Specific to our graphic
         extent = "410 92";
         minExtent = "8 2";
         horizSizing = "left";
         vertSizing = "top";
         profile = "GuiDefaultProfile";
         visible = "0";
         active = "1";
         command = "Canvas.pushDialog( ConfirmExitDlg );";
         tooltipProfile = "GuiToolTipProfile";
         hovertime = "1000";
         isContainer = "0";
         internalName = "DisconnectButton";
         hidden = "1";
         canSave = "1";
         canSaveDynamicFields = "0";
      };
      %this.add(%button);
   }
   
   // Hide the disconnect button until we need it
   %this-->DisconnectButton.setVisible(false);
}

function LoadingGui::showDisconnectButton(%this)
{
   %this-->DisconnectButton.setVisible(true);
}
