#version 330 core

in vec3 vPosition;

uniform vec3 skyColor;
uniform vec3 horizonColor;

out vec4 color;

void main()
{
	float y = abs(vPosition.y);
	vec3 gradient = mix(horizonColor, skyColor, y);
	color = vec4(gradient, 1);

	//color = vec4(vec3(abs(vPosition.x), abs(vPosition.y), abs(vPosition.z)), 1);
}