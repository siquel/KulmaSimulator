#version 330
in vec3 inPosition;
uniform mat4 projection;
void main() {
	gl_Position = vec4(inPosition, 0) * projection;
}