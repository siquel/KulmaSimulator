#include "resources.h"
#include <iostream>
#include <fstream>
#include <cassert>


Resource::Resource() {

}

Resource::~Resource() {

}

Texture::Texture() : Resource(), width(0), height(0) {

}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

bool Texture::readFromFile(const std::string& path) {
	// we only accept pngs
	std::string fullpath(path + ".png");
	std::vector<unsigned char> png;

	lodepng::load_file(png, fullpath);
	std::vector<unsigned char> pixels;
	size_t error = lodepng::decode(pixels, width, height, png.data(), png.size());

	if (error) {
		std::fprintf(stderr, "Error loading texture file %s\n", lodepng_error_text(error));
		return false;
	}
	// create new name for texture
	glGenTextures(1, &id);
	// bind it so we can modify it
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
	// set GL_NEAREST filter on
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// unbind
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

const GLuint& Texture::getId() const {
	return id;
}

bool Effect::readFromFile(const std::string& path) {
	std::string vertex(path + ".vert");
	std::string fragment(path + ".frag");
	program = compileShaders(readFile(vertex).c_str(), readFile(fragment).c_str());
	return true;
}

std::string Effect::readFile(const std::string& filepath) {
	std::ifstream fileStream(filepath, std::ios::binary);
	assert(fileStream.good());

	fileStream.seekg(0u, std::ios::end);
	std::string source;
	source.reserve(static_cast<unsigned int>(fileStream.tellg()));
	fileStream.seekg(0u, std::ios::beg);
	source.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
	assert(fileStream.good());

	return source;
}

GLuint Effect::compileShaders(const char* vertexSrc, const char* fragmentSrc) {
	GLint result = GL_FALSE;
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// create vertexshader
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	assert(result == GL_TRUE);

	// create fragment shader
	glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	assert(result == GL_TRUE);

	GLuint program = glCreateProgram();
	assert(program != 0);
	// attach shaders
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);


	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	assert(result == GL_TRUE);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}

void Effect::bind() const {
	glUseProgram(program);
}

void Effect::unbind() const {
	glUseProgram(0);
}

GLuint Effect::getProgram() const {
	return program;
}

Effect::~Effect() {
	glDeleteProgram(program);
}

Effect::Effect() : program(0) { }