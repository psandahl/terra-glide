#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

// Premultiplied mvp matrix.
uniform mat4 mvpMatrix;

// Premultiplied normal matrix which put normals into view space.
uniform mat3 normalMatrix;

// The maximum height of the terrain.
uniform float terrainHeight;

// The terrain is shaded using two gradients, where each
// gradient have two colors. The colors are enumerated
// from lower terrain to upper.
uniform vec3 terrainColor0;
uniform vec3 terrainColor1;
uniform vec3 terrainColor2;
uniform vec3 terrainColor3;

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
	float height = position.y / terrainHeight;

	vec3 color = mix(terrainColor0, terrainColor1, smoothstep(0.0, 0.2, height));
	color = mix(color, terrainColor2, smoothstep(0.2, 0.7, height));
	return mix(color, terrainColor3, smoothstep(0.7, 1.0, height));
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