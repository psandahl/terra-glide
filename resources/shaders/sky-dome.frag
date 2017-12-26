#version 330 core

in vec3 vPosition;

out vec4 color;

void main()
{
	color = vec4(vec3(abs(vPosition.x), abs(vPosition.y), abs(vPosition.z)), 1);
}