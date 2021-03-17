#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texPos;

out vec2 TexCoord;
uniform mat4 projection;
uniform mat4 model;

void main()
{
	TexCoord = texPos;
	gl_Position =  projection * model * vec4(position, 1.0);
}