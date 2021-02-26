# Sokoban
Sokoban game in C

# Quick Start:

### GNU/Linux : <br/>
`$ sudo apt install libglfw3-dev libglew-dev` <br/>
`$ sudo chmod +x build.sh` <br/>
`$ ./build.sh` <br/>

### Windows (Visual Studio): <br/>
In order to make the program work properly, you need to put the required dlls to `output/` directory (`glew32.dll` , `glfw3.dll`). <br/>
Initialize enviroment variables: <br/>
`$ vcvarsall.bat x64` <br/>
Build the program: <br/>
`$ .\build.bat`

# SS
### Testing projection matrices:
![](https://i.imgur.com/kat0UEA.png)

```
        position = vec3_create(300.0f, 300.0f, 0.0f);
        draw_quad(context, &position, 70.0f);

		position = vec3_create(200, 200, 0.0f);
        draw_colored_quad(context, &position, &color, 120.0f);

```