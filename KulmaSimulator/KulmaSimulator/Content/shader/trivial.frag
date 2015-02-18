#version 330
in vec2 texCoords;
in vec3 normals;
uniform sampler2D tex;

void main() {
	vec4 diffuse = texture2D(tex, vec2(texCoords.x, -texCoords.y));
	float a = diffuse.x;
	gl_FragColor = vec4(diffuse.xy, normals.x, 1);
}