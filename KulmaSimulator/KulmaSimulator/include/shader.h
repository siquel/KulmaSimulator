#pragma once
#include <GL\glew.h>
class Shader {
private:
	GLuint program = 0;
	bool loaded;

public:
	Shader();
	~Shader();

	void loadShader(const char* vert, const char* frag);
	void unloadShader();
	void bind() const;
	void unbind() const;
	inline GLuint getProgram() const {
		return program;
	}
};