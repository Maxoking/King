#version 330 core

//in vec4 pos;
out vec4 color;
uniform vec2 light_pos;
uniform vec4 base_color = vec4(0,0,1,1);

in DATA
{
	vec4 position;
} fs_in;

void main()
{
	float intensity = 1 / length(fs_in.position.xy - light_pos);
	//color = vec4(1,0,0,1) * intensity * 20;
	color = base_color * intensity * 20;
}	
