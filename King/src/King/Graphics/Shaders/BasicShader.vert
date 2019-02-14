#version 330 core

layout (location = 0) in vec3 position;
out vec4 pos;

uniform mat4 proj_mat;
uniform mat4 view_mat;


void main()
{
	pos = vec4(position, 1.f);
	gl_Position = proj_mat * pos;
} 