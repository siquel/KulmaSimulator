#version 330
out vec4 outColour;
in vec2 texCoords;
in vec4 color;
uniform sampler2D tex;
void main() {
	outColour = texture2D(tex, vec2(texCoords.x, -texCoords.y)) * color;
}