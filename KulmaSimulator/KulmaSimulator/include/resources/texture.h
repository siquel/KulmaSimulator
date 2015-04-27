#ifndef TEXTURE_H
#define TEXTURE_H
#include <gl/glew.h>
#include "resource.h"
class Texture : public Resource {
public:
	size_t width;
	size_t height;
	GLuint id;
public:
	Texture(GLuint id, size_t w, size_t h);
	Texture();
	~Texture();
	bool readFromFile(const std::string& path);
	const GLuint& getId() const;
};

#endif