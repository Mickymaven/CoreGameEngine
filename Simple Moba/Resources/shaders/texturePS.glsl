//File: texturePS.glsl
// Pixel Shader

#version 400

in vec2 texCoord;

out vec4 outputColor;

uniform sampler2D shaderTexture;

void main(void)
{
	vec4 textureColor;

	textureColor = texture(shaderTexture,texCoord);
	outputColor = textureColor;
}
