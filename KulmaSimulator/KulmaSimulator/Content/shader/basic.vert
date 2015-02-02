#version 330

layout(location = 0)

in vec3 inPosition;
in vec3 color;
layout(location = 1)
in vec2 coords;
out vec2 texCoords;
void main() {
	gl_Position = vec4(inPosition, 1.0);
	texCoords = coords;
}