#ifndef EFFECT_H
#define EFFECT_H
#include "resource.h"
#include <gl/glew.h>
class Effect : public Resource {
private:
	std::string readFile(const std::string& path);
	GLuint compileShaders(const char* vertexSrc, const char* fragmentSrc);
	GLuint program = 0;
public:
	Effect();
	~Effect();
	bool readFromFile(const std::string& path);
	void bind() const;
	void unbind() const;
	GLuint getProgram() const;
};

#endif