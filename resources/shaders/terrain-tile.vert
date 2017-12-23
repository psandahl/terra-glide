#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

// Premultiplied mvp matrix.
uniform mat4 mvpMatrix;

// Premultiplied normal matrix which put normals into view space.
uniform mat3 normalMatrix;

// The ambient light; color and strength.
uniform vec3 ambientColor;
uniform float ambientStrength;

// The sun's transformed direction and color.
uniform vec3 sunDirection;
uniform vec3 sunColor;

// The color to be interpolated for the fragment shader.
out vec3 fragmentColor;

// Helper functions.
vec3 terrainColor();
vec3 ambientLight();
vec3 sunLight();

void main()
{
	fragmentColor = terrainColor() * (ambientLight() + sunLight());
	gl_Position = mvpMatrix * vec4(position, 1);
}

// Select the terrain color from the terrain's height.
vec3 terrainColor()
{
	return vec3(86.0 / 255.0, 125.0 / 255.0, 70.0 / 255.0);
}

// Calculate the ambient light.
vec3 ambientLight()
{
	return ambientColor * ambientStrength;
}

// Calculate the sun light.
vec3 sunLight()
{
	vec3 transformedNormal = normalize(normalMatrix * normal);
	float diffuse = max(dot(transformedNormal, sunDirection), 0);

	return sunColor * diffuse;
}