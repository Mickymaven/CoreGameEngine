////////////////////////////////////////////////////////////////////////////////
// Filename: lightPS.glsl
////////////////////////////////////////////////////////////////////////////////
#version 400

in vec2 texCoord;
in vec3 normal;

out vec4 outputColor;

uniform sampler2D shaderTexture;
uniform vec3 lightDirection;
uniform vec4 diffuseLightColor;
uniform vec4 ambientLight;

void main(void)
{
	vec4 textureColor;
	vec4 color;
	vec3 lightDir;
	float lightIntensity;

	textureColor = texture(shaderTexture, texCoord);

	color = ambientLight;

	lightDir = -lightDirection;

	lightIntensity = clamp(dot(normal, lightDir), 0.0f, 1.0f);

	if(lightIntensity > 0.0f)
	{
		color += (diffuseLightColor * lightIntensity);
	}

	color = clamp(color, 0.0f, 1.0f);

	outputColor = color * textureColor;

}