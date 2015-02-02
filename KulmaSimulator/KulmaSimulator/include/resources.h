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
	//bool isBound() const;
	
};

#endif