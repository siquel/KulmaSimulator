#include "simulator.h"
#include <iostream>

Simulator::Simulator() {

}
Simulator::~Simulator() {}

void Simulator::update() {}
void Simulator::draw() { 
	/*effect->bind();

	glBindVertexArray(vao);
	
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->getId());
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
	
	effect->unbind();*/

	spriteBatch.begin(SpriteSortMode::Deferred);
	spriteBatch.draw(pmath::Vec3f(0.5f, 0.5f, 0.5f), texture);
	spriteBatch.end();
}

void Simulator::initialize() {
	getInput().bind("Zaaryus", [](InputArgs args) {
		if (args.state == InputState::PRESSED)
			std::cout << "a pressed" << std::endl;
	}, std::vector < ITrigger* > { new KeyTrigger(SDLK_a) });
	texture = content.load<Texture>("temp");
	effect = content.load<Effect>("shader\\basic");
	
	spriteBatch.init();
	/*
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, uv)));
	*/
}
