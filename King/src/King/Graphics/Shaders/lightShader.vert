#version 330 core
			
layout(location = 0) in vec3 a_Position;


uniform mat4 view_proj_mat;
uniform mat4 model_mat = mat4(1.f);

out vec3 v_Normal;
void main()
{
	
	vec4 pos = vec4(a_Position, 1.0);

	gl_Position = view_proj_mat * model_mat * pos;
}