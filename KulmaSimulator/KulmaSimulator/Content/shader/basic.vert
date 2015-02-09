#version 330

layout(location = 0)
in vec3 inPosition;
layout(location = 1)
in vec4 inColor;
layout(location = 2)
in vec2 coords;
out vec2 texCoords;
out vec4 color;
uniform mat4 enterTheMatrix;

void main() {
	gl_Position = enterTheMatrix * vec4(inPosition, 1.0);
	texCoords = coords;
	color = inColor;
}