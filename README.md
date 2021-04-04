# Sokoban
Sokoban game in C

# Quick Start:

### GNU/Linux : <br/>
`$ sudo apt install libglfw3-dev libglew-dev` <br/>
`$ sudo chmod +x build.sh` <br/>
`$ ./build.sh` <br/>

### FreeBSD : <br/>
`$ sudo pkg install -y glew glfw` <br/>
`$ sudo chmod +x build.sh` <br/>
`$ ./build.sh` <br/>

### Windows (Visual Studio): <br/>
In order to make the program work properly, you need to put the required dlls to `output/` directory (`glew32.dll` , `glfw3.dll`). <br/>
Initialize environment variables: <br/>
`$ vcvarsall.bat x64` <br/>
Build the program: <br/>
`$ .\build.bat`
