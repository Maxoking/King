#version 330 core

layout (location = 0) in vec4 position;
//out vec4 pos;

uniform mat4 proj_mat;
uniform mat4 view_mat;
uniform mat4 model_mat = mat4(1.f);

out DATA
{
	vec4 position;
} vs_out;


void main()
{
	//pos = vec4(position, 1.f);
	gl_Position = proj_mat * view_mat * model_mat * position;
	vs_out.position = model_mat * position;
} 