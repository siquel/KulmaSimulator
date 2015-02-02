#version 330
out vec4 outColour;
in vec2 texCoords;
uniform sampler2D tex;
void main() {
	outColour = texture(tex, vec2(texCoords.x, -texCoords.y) );
}