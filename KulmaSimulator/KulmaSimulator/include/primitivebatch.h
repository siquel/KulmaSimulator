#ifndef PRIMITIVEBATCH_H
#define PRIMITIVEBATCH_H
#include "GL\glew.h"
class PrimitiveBatch {
public:
	PrimitiveBatch(size_t maxIndices, size_t maxVertices, size_t vertexSize);
	void begin();
	void end();

private:
	GLuint VBO;
	GLuint IBO;
	GLuint VAO;
	size_t maxIndices;
	size_t maxVertices;
	size_t currentVertex;
	size_t currentIndex;
	size_t vertexSize;
	bool hasBegun;


	void flushBatch();
	void createBuffer(size_t size, GLenum type, GLuint* buf);
};

#endif