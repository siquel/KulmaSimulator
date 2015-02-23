#include "component/meshrenderer.h"
#include "simulator.h"
#include "component/transform.h"
#include "Entity.h"
MeshRenderer::MeshRenderer(Mesh* mesh) : mesh(mesh) {
	enable();
}

MeshRenderer::~MeshRenderer() {}

void MeshRenderer::onDraw(SpriteBatch& spriteBatch) {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	effect->bind();
	glBindTexture(GL_TEXTURE_2D, mesh->getMaterials()[0].getTexture()->getId());

	GLuint mvploc = glGetUniformLocation(effect->getProgram(), "MVP");
	getOwner()->getComponent<Transform>()->rotate(0.05f, glm::vec3(0.0f, 1.f, -0.0f));
	glUniformMatrix4fv(mvploc, 1, GL_FALSE, glm::value_ptr(Simulator::getInstance().getCamera().getCamera() * getOwner()->getComponent<Transform>()->getTransform()));

	glDrawArrays(GL_TRIANGLES, 0, mesh->getVertices().size());
	
	effect->unbind();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glAssert();
}

void MeshRenderer::onInitialize() {



	effect = Simulator::getInstance().getContent().load<Effect>("shader/trivial");

	glGenVertexArrays(1, &VAO);
	glAssert();
	glBindVertexArray(VAO);
	glAssert();
	glGenBuffers(1, &VBO);
	glAssert();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, nullptr);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 5));

	glAssert();
	glBufferData(GL_ARRAY_BUFFER, mesh->getVertices().size() * sizeof(GLfloat), mesh->getVertices().data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glAssert();
}