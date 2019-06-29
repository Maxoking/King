#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 proj_mat;
uniform mat4 view_mat;
uniform mat4 model_mat = mat4(1.f);

out vec3 v_Position;
out vec4 v_Color;
void main()
{
	v_Position = a_Position;
	v_Color = a_Color;
	
	vec4 pos = vec4(a_Position, 1.0);
	//gl_Position = proj_mat * view_mat * model_mat * position;
	gl_Position = proj_mat * view_mat * model_mat * pos;	
	//gl_Position = vec4(a_Position, 1.0);
	
	gl_Position = proj_mat * view_mat * model_mat * pos;
}