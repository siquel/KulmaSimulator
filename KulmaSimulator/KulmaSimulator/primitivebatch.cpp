#include "primitivebatch.h"
#include <stdexcept>
PrimitiveBatch::PrimitiveBatch(size_t maxIndices, size_t maxVertices, size_t vertexSize)
	: IBO(0), VBO(0), VAO(0), maxIndices(maxIndices), 
	maxVertices(maxVertices), vertexSize(vertexSize), hasBegun(false), currentVertex(0), currentIndex(0) {

}

void PrimitiveBatch::begin() {
	if (hasBegun) {
		throw std::logic_error("End must be called!");
	}
}

void PrimitiveBatch::end() {
	if (!hasBegun) return;

	flushBatch();
}

void PrimitiveBatch::flushBatch() {

}

void PrimitiveBatch::createBuffer() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, maxVertices * vertexSize, nullptr, GL_DYNAMIC_DRAW);

	
}

