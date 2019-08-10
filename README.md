# Chroma-Engine
A Render Engine
![Chroma Logo](resources/logo.png)
Hebele hübele

## Some visuals from chroma
![Rotating Cube](resources/images/cube.gif)  
![Multiple Cameras](resources/images/multi-cam.gif)  
![obj Loader](resources/images/load.gif)  
![textures](resources/images/texture.gif)  
![phong shading](resources/images/phong.gif)  
<img src= "resources/images/phong.PNG" height="270" width="480">  
<img src= "resources/images/dirl.gif" height="155" width="276"> <img src= "resources/images/spotl.gif" height="155" width="276"> <img src= "resources/images/pointl.gif" height="155" width="276"> 

## Build Instructions (for Windows)
Download [CMake](https://cmake.org/download/) if you dont have it already.  
Launch CMake  
Enter the "Where is the source code:" as the root directory of the repository(**where CMakeLists.txt is**).  
Enter the "Where to build binaries" as the **root_directory_of_the_repo/build**.  
Press to **Cofigure** and enter your compiler preferences and VS version.
Press **Generate**.  
Go to build folder and find **chroma.sln** file and double click.  
Build and run in VS.  

**NOTE:** if VS gives an error about that it cannot find .exe file try setting the exe directory manually by:  
Rigth click to ALL_BUILD -> properties -> Debugging-> command -> <browse> -> find at bin/Debug/chroma.exe
