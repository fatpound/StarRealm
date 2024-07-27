# StarRealm

![starrealm2](https://github.com/fatpound/StarRealm/assets/84704675/441707c8-4ae2-42c7-bfda-f2a721d83de2)

This is a game/animation of some randomly-generated 2D stars in 3D space.

Building
--------
Install the latest version of Visual Studio 2022.\
Install the Desktop development with C++ workload in Visual Studio Installer along with\
the experimental Modules support.\
Install Game Programming with C++ workload.\
Open Visual Studio.\
Clone the repo to Visual Studio.\
Select "Show All Files" in the Solution Explorer window.\
Then you can build the project. (Select Release, not Debug)

About Examples
--------------
I added 6 types of stars:

Filled or Hollow\
Blend or ColorIndexed\
SingleColor or MultiColor

The stars just rotate around their centres\
You can zoom in or out with the mouse wheel (Z axis movement)\
You can move around the space in the X and Y axis using the left mouse click\
You can play the game in fullscreen if you build it in Release mode\
If you want to lower the memory usage of the game, then try 4, 2 or 1 value for the msaa_quality_ in Graphics.ixx file. The tradeoff is, stars will look slightly worse than before. If you are using a newer Graphics card, then you should set this to 16 for maximum quality.\
Hold SPACE to stop stars\
Press ESC to exit

Copyright (c) 2024 fatpound 
