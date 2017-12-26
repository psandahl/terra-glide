#version 330 core

in vec3 vPosition;

uniform vec3 skyColor;
uniform vec3 horizonColor;
uniform vec3 fogColor;

out vec4 color;

const float fogHeight = 0.3;

void main()
{
	float y = abs(vPosition.y);
	vec3 skyGradient = mix(horizonColor, skyColor, y);

	color = vec4(mix(fogColor, skyGradient, smoothstep(0, fogHeight, y)), 1);
}