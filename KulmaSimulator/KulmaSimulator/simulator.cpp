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
	spriteBatch.draw(pmath::Vec2f(0.5f, 0.5f), texture);
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
}
