#include "primitivebatch.h"
#include <stdexcept>
#include <cassert>
PrimitiveBatch::PrimitiveBatch(size_t maxIndices, size_t maxVertices, size_t vertexSize)
	: IBO(0), VBO(0), VAO(0), maxIndices(maxIndices), 
	maxVertices(maxVertices), vertexSize(vertexSize), hasBegun(false), currentVertex(0), currentIndex(0) {

	assert(maxIndices > 0);
	// index buffer
	createBuffer(maxIndices * sizeof(unsigned short), GL_ELEMENT_ARRAY_BUFFER, &IBO);
	// vertex buffer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	createBuffer(maxVertices * vertexSize, GL_ARRAY_BUFFER, &VBO);
	
}

void PrimitiveBatch::begin() {
	if (hasBegun) {
		throw std::logic_error("End must be called!");
	}
	hasBegun = true;
}

void PrimitiveBatch::end() {
	if (!hasBegun) return;

	flushBatch();
}

void PrimitiveBatch::flushBatch() {

}

void PrimitiveBatch::createBuffer(size_t size, GLenum type, GLuint* buf) {

	glGenBuffers(1, buf);
	glBindBuffer(type, *buf);
	glBufferData(type, size, nullptr, GL_DYNAMIC_DRAW);	
}

