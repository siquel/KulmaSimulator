#ifndef RESOURCES_H
#define RESOURCES_H
#include <string>
#include <lodepng/lodepng.h>
#include <gl/glew.h>

class Resource {
public:
	Resource();
	virtual ~Resource();
	virtual bool readFromFile(const std::string& path) = 0;
};

class Texture : public Resource {
private:
	size_t width;
	size_t height;
	GLuint id;
public:
	Texture();
	~Texture();
	bool readFromFile(const std::string& path);
	const GLuint& getId() const;
};

#endif