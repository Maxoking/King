#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;


uniform mat4 view_proj_mat;
uniform mat4 model_mat = mat4(1.f);
uniform mat4 light_space_mat;

out vec3 v_FragPosition;
out vec4 v_FragPosLightSpace;
out vec3 v_Normal;
out vec2 v_TexCoord;


void main()
{
	v_Normal = a_Normal;
	
	vec4 pos = vec4(a_Position, 1.0);
	v_FragPosition = vec3(model_mat * pos);
	v_FragPosLightSpace = light_space_mat * model_mat * vec4(v_FragPosition, 1.0);
	v_TexCoord = a_TexCoord;

	gl_Position = view_proj_mat * model_mat * pos;
}