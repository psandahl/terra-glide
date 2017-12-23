#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

// Premultiplied mvp matrix.
uniform mat4 mvp;

// The color to be interpolated for the fragment shader.
out vec3 fragmentColor;

// Helper functions.
vec3 terrainColor();

void main()
{
	fragmentColor = terrainColor();
	gl_Position = mvp * vec4(position, 1);
}

// Select the terrain color from the terrain's height.
vec3 terrainColor()
{
	return vec3(86.0 / 255.0, 125.0 / 255.0, 70.0 / 255.0);
}