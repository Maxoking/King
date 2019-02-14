#version 330 core

in vec4 pos;
out vec4 color;
uniform vec2 light_pos;

void main()
{
	float intensity = 1/length(pos.xy - light_pos);
	color = vec4(1.f,0,0,1) *intensity;
} 