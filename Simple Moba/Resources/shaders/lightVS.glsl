////////////////////////////////////////////////////////////////////////////////
// Filename: lightVS.glsl
////////////////////////////////////////////////////////////////////////////////
#version 400

in vec3 inputPosition;
in vec2 inputTexCoord;
in vec3 inputNormal;

out vec2 texCoord;
out vec3 normal;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
	gl_Position = worldMatrix * vec4(inputPosition, 1.0f);
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;

	texCoord = inputTexCoord;

	normal = mat3(worldMatrix) * inputNormal;

	normal = normalize(normal);
}
