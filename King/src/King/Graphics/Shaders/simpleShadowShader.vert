#version 330 core
			
layout(location = 0) in vec3 a_Position;

uniform mat4 light_space_mat;
uniform mat4 model_mat;

void main()
{
	vec4 pos = vec4(a_Position, 1.0);
	gl_Position = light_space_mat * model_mat * pos;
}