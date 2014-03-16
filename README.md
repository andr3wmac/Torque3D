Torque 3D v3.5
==============

This branch combines D3D9-Refactor by Anis with VS2013 fixes by signmotion. This version requires Windows 8 SDK to be installed instead of DirectX SDK since it is now deprecated.

D3D-Refactor by Anis
----------------

* Better *.cpp organization / code cleaning
* Removed D3DX calls dependencies. (deprecated by Microsoft)
* Removed D3D9 XBOX360 old reference.
* Shader/Constant buffer refactor with a custom parser.
* gfxD3D9Shader total refactor.
* Mipmap autogen fixes
* Minor fixes under cubemap
* Speed improved on texture loading
* Removed 24bit format (deprecated since DX10) (i convert it to 32bit) 
* Some performance improvement (especially under a lot of dynamic_cast used in wrong context)
* Removed fixed pipeline (deprecated by Microsoft since DX10)
* Many other minor bug fixed.
