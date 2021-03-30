#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in float color_num;

uniform mat4 projection;
uniform mat4 model;

out float color_n;

void main()
{
	gl_Position =  projection * model * vec4(position, 1.0);
	color_n = color_num;
}