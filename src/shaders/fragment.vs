#version 460 core

uniform vec4 u_color;
out vec4 color;

in float color_n;

void main()
{
	if(color_n == 1.0){
			   color = vec4(1.0, 0.0, 0.0, 1.0);
	}
	else if(color_n == 0.0){
			   color = vec4(0.0, 1.0, 0.0, 1.0);
	}

}