#include "bulletdebugdraw.h"
#include "simulator.h"
GLDebugDraw::GLDebugDraw() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, nullptr);
	size_t size = 512 * 4;
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GL_FLOAT) * 3, nullptr, GL_DYNAMIC_DRAW);
	vertices.reserve(size);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	effect = Simulator::getInstance().getContent().load<Effect>("shader\\engine\\bullet");
}

GLDebugDraw::~GLDebugDraw() {

}

void GLDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor) {
	vertices.push_back(from.getX());
	vertices.push_back(from.getY());
	vertices.push_back(from.getZ());
	vertices.push_back(to.getX());
	vertices.push_back(to.getY());
	vertices.push_back(to.getZ());
}

void GLDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
	vertices.push_back(from.getX());
	vertices.push_back(from.getY());
	vertices.push_back(from.getZ());
	vertices.push_back(to.getX());
	vertices.push_back(to.getY());
	vertices.push_back(to.getZ());
}

void GLDebugDraw::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {

}

void GLDebugDraw::reportErrorWarning(const char* warningString) {

}

void GLDebugDraw::draw3dText(const btVector3& location, const char* textString) {

}


void GLDebugDraw::draw() {
	// TODO enter the matrix
	effect->bind();

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());

	glDrawArrays(GL_LINES, 0, vertices.size());
	glAssert();
	effect->unbind();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	vertices.clear();
}