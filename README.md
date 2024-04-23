# StarRealm

![starrealm2](https://github.com/fatpound/StarRealm/assets/84704675/441707c8-4ae2-42c7-bfda-f2a721d83de2)

In order to build, you must have the latest version of MSVC and C++20 modules must be installed. Then you can clone the repo to Visual Studio 2022.

I added 6 types of stars:

Blend or ColorIndexed\
Filled or Hollow\
Indexed or Single <- ColorIndexed

The stars are in a 3D space\
The stars just rotate around their centres\
You can zoom in or out with the mouse wheel\
You can move around the space in the X and Y axis using the left mouse click\
You can play the game in fullscreen if you build it in Release mode\
If you want to lower the memory usage of the game, then try 8, 4, 2 or 1 value for the MSAA_QUALITY in D3D11Graphics.cpp file. The tradeoff is, stars will look slightly worse than before.\
Press SPACE to stop stars\
Press ESC to exit

Copyright (c) 2024 fatpound 
