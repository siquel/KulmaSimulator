#version 330

layout(location = 0)
in vec3 inPosition;
layout(location = 1)
in vec4 color;
layout(location = 2)
in vec2 coords;
out vec2 texCoords;

void main() {
	gl_Position = vec4(inPosition, 1.0);
	texCoords = coords;
}