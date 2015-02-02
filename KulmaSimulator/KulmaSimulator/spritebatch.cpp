#include "spritebatch.h"



SpriteBatch::SpriteBatch() : hasBegun(false), VAO(0), VBO(0), IBO(0) {

}

SpriteBatch::~SpriteBatch() {

}

void SpriteBatch::begin() {
	if (hasBegun) {
		throw std::logic_error("End must be called");
	}
	hasBegun = true;
}

void SpriteBatch::end() {

}

void SpriteBatch::draw(const pmath::Vec4f& rekt) {
	SpriteInfo info;
	
}

void SpriteBatch::createIndexBuffer() {
	//indices.reserve()
	/*glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, , )*/
}

void SpriteBatch::createVertexArray() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// position, color, uv
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(offsetof(SpriteInfo, pos)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(offsetof(SpriteInfo, color)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(offsetof(SpriteInfo, uv)));

	glBindVertexArray(0);
}