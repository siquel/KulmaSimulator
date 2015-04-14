#include "box2Ddebugdraw.h"
#include "util.h"
#include "simulator.h"

Box2DDebugDraw::Box2DDebugDraw() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
	glBufferData(GL_ARRAY_BUFFER, 512 * sizeof(float) * 8, nullptr, GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	effect = Simulator::getInstance().getContent().load<Effect>("shader\\engine\\box2d");
}

Box2DDebugDraw::~Box2DDebugDraw() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Box2DDebugDraw::DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color) {

}
void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color) {
	
	GLfloat glverts[8] = { 0 };
	for (int i = 0; i < vertexCount; i++) {
		glverts[i * 2] = vertices[i].x;
		glverts[i * 2 + 1] = vertices[i].y;
	}
	for (size_t i = 0; i < 8u; i++) {
		this->vertices.push_back(glverts[i]);
	}
}
void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {

}
void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {

}
void Box2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {

}
void Box2DDebugDraw::DrawTransform(const b2Transform& tf) {

}

void Box2DDebugDraw::doDraw() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	effect->bind();
	size_t size = vertices.size();
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * size, vertices.data());
	glAssert();
	glDrawArrays(GL_LINES, 0, size);

	effect->unbind();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	vertices.clear();
}