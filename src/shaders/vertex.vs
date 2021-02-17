#version 460 core
layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 model;

void main()
{
	//gl_Position = vec4(position, 1.0);
	gl_Position = projection * model * vec4(position, 1.0);
}