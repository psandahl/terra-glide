#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 mvpMatrix;

out vec3 vPosition;

void main()
{
	vPosition = position;
	gl_Position = mvpMatrix * vec4(position, 1);
}