#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

// Premultiplied mvp matrix.
uniform mat4 mvpMatrix;

// View matrix (for calculation of fog distance).
uniform mat4 viewMatrix;

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

// Fog color and fog distance.
uniform vec3 fogColor;
uniform float fogDistance;

// The color to be interpolated for the fragment shader.
out vec3 fragmentColor;

// Helper functions.
vec3 terrainColor();
vec3 ambientLight();
vec3 sunLight();

void main()
{
	vec3 transformedPosition = (viewMatrix * vec4(position, 1)).xyz;
	float dist = distance(vec3(0), transformedPosition);
	//float fogFactor = smoothstep(0, fogDistance, dist);
	//float fogFactor = 1.0 - clamp((fogDistance - dist) / (fogDistance - 100.0), 0.0, 1.0);
	float fogFactor = 1.0 - clamp(exp(-0.003 * dist), 0.0, 1.0);

	vec3 withoutFog = terrainColor() * (ambientLight() + sunLight());
	fragmentColor = mix(withoutFog, fogColor, fogFactor); 

	gl_Position = mvpMatrix * vec4(position, 1);
}

// Select the terrain color from the terrain's height.
vec3 terrainColor()
{
	float height = position.y / terrainHeight;

	vec3 color = mix(terrainColor0, terrainColor1, smoothstep(0.0, 0.5, height));
	color = mix(color, terrainColor2, smoothstep(0.5, 0.6, height));
	return mix(color, terrainColor3, smoothstep(0.6, 1.0, height));
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