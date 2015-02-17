#version 330

layout(location = 0) 
in vec3 inPosition;
layout(location = 1)
in vec2 inTexcoords;

uniform mat4 MVP;
out vec2 texCoords;

void main() {
	gl_Position = MVP * vec4(inPosition, 1f);
	texCoords = inTexcoords;
}