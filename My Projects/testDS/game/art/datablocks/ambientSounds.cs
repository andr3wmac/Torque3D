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
// Ambient sounds for the police chatter next to the police cars
//-----------------------------------------------------------------------------

datablock SFXProfile (SFX_PoliceRadio1)
{
   fileName = "art/sound/CT_fx/ambient/POLICE RADIO1.wav";
   description = "AudioClosest3D";
   preload = true;
};

datablock SFXProfile (SFX_PoliceRadio2)
{
   fileName = "art/sound/CT_fx/ambient/POLICE RADIO2.wav";
   description = "AudioClosest3D";
   preload = true;
};

datablock SFXProfile (SFX_PoliceRadio3)
{
   fileName = "art/sound/CT_fx/ambient/POLICE RADIO3.wav";
   description = "AudioClosest3D";
   preload = true;
};

datablock SFXProfile (SFX_PoliceRadio4)
{
   fileName = "art/sound/CT_fx/ambient/POLICE RADIO4.wav";
   description = "AudioClosest3D";
   preload = true;
};

datablock SFXPlayList (PoliceRadioChatter)
{
    track[0] = SFX_PoliceRadio1;
    track[1] = SFX_PoliceRadio2;
    track[2] = SFX_PoliceRadio3;
    track[3] = SFX_PoliceRadio4;
   random = "OrderedRandom";
   description = "AudioClosestLoop3D";
   delayTimeOut[0] = "7";
   delayTimeOutVariance[0] = "5 5";
   delayTimeOut[1] = "7";
   delayTimeOutVariance[1] = "5 5";
   delayTimeOut[2] = "7";
   delayTimeOutVariance[2] = "5 5";
   delayTimeOut[3] = "7";
   delayTimeOutVariance[3] = "5 5";
   numSlotsToPlay = "4";
   replay[0] = "StartNew";
   replay[1] = "StartNew";
   replay[2] = "StartNew";
   replay[3] = "StartNew";
};

//-----------------------------------------------------------------------------
// Ambient sounds for the helicopter blades
//-----------------------------------------------------------------------------

datablock SFXProfile (HelicopterBlades)
{
   fileName = "art/sound/CT_fx/ambient/HELICOPTER - BLADE.wav";
   description = "AudioClosestLoop3D";
   preload = true;
};

datablock SFXProfile (ElectricBuzz)
{
   fileName = "art/sound/CT_fx/ambient/BUZZ.wav";
   description = "AudioClosestLoop3D";
   preload = true;
};

datablock SFXProfile (WaterDrips)
{
   fileName = "art/sound/CT_fx/ambient/tunnel.wav";
   description = "AudioClosestLoop3D";
   preload = true;
};

//-----------------------------------------------------------------------------
// Generic Dry Fire sounds for the weapons
//-----------------------------------------------------------------------------
datablock SFXProfile (MachineGunDryFire)
{
   fileName = "art/sound/CT_fx/weapons/SCAREMPTY.wav";
   description = "AudioClosest3D";
   preload = true;
};

datablock SFXProfile (PistolDryFire)
{
   fileName = "art/sound/CT_fx/weapons/PISTOLEMPTY.wav";
   description = "AudioClosest3D";
   preload = true;
};
