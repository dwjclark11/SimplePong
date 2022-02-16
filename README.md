# Simple Pong w/ C++ and SFML 
## Introduction
This is a fun little of Pong written in C++ using SFML. I made this game with my kids for a little bit of fun together.
Right now there is only one state [GameState]; however, I will be added more states to change the difficulty, multiball mode ect.

*    The balls multiply based on the speed level.
*    There is some very simple AI that could be improved.
*    Currently not resizable (Resolution: [1920 x 1080]). Make sure your resolution settings are set to that.

## Controls
| Key | Action |
| --- | ------ |
| W | Player 1 Up |
| S | Player 1 Down |
| Up | Player 2 Up | 
| Down | Player 2 Down | 


## Gameplay Video
*    Check this out!

https://user-images.githubusercontent.com/63356975/154179520-2fa466ad-4a80-4edb-a5d3-c225ea1564e1.mp4

## How to Build
This project currently uses Visual Studio 2019 Community and has not been tested on different systems/IDEs and it should build 
direct out of the box.
* Step 1)
    *  Clone the repo
* Step 2)
    * Run the GenerateSolution.bat file
    * This should run the premake5.lua file and create a visual studio .sln
* Step 3)
    *  Open the solution and build and run. It should work from there.
   

