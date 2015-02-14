#include "PrimitiveBatch.h"
#include <stdexcept>
#include <cassert>
PrimitiveBatchBase::PrimitiveBatchBase(size_t maxIndices, size_t maxVertices, size_t vertexSize)
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

void PrimitiveBatchBase::begin() {
	if (hasBegun) {
		throw std::logic_error("End must be called!");
	}
	hasBegun = true;
}

void PrimitiveBatchBase::end() {
	if (!hasBegun) return;

	flushBatch();
}

void PrimitiveBatchBase::flushBatch() {

}

void PrimitiveBatchBase::createBuffer(size_t size, GLenum type, GLuint* buf) {

	glGenBuffers(1, buf);
	glBindBuffer(type, *buf);
	glBufferData(type, size, nullptr, GL_DYNAMIC_DRAW);	
}

