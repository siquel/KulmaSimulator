#ifndef PRIMITIVEBATCH_H
#define PRIMITIVEBATCH_H
#include "GL\glew.h"
#include "GLM.h"
struct VertexPositionColor {
	glm::vec3 position;
	glm::vec4 color;
};

class PrimitiveBatchBase {
public:
	PrimitiveBatchBase(size_t maxIndices, size_t maxVertices, size_t vertexSize);

	void begin();
	void end();

protected:
	void draw(GLenum type, bool isIndexed, unsigned short* indices, size_t indexCount, size_t vertexCount, void** vertices);
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
template<typename TVertex>
class PrimitiveBatch : public PrimitiveBatchBase {
	static const size_t DefaultBatchSize = 2048;

public:
	PrimitiveBatch(size_t maxIndices = DefaultBatchSize * 3, 
		size_t maxVertices = DefaultBatchSize) 
		: PrimitiveBatchBase(maxIndices, maxVertices, sizeof(TVertex)) {}

	void drawTriangle(TVertex const& v1, TVertex const& v2, TVertex const& v3) {
		TVertex vertices[] = { v1, v2, v3 };
		PrimitiveBatchBase::draw(GL_TRIANGLES, false, nullptr, 0, 3, vertices);
	}

	void drawQuad(TVertex const& v1, TVertex const& v2, TVertex const& v3, TVertex const& v4) {
		static const unsigned short* indices[] = { 0, 1, 2, 1, 3, 2 };
		TVertex vertices = { v1, v2, v3, v4 };
		PrimitiveBatchBase::draw(GL_TRIANGLES, true, indices, 6, 4, vertices);
	}
};

#endif