#include "simulator.h"
#include <iostream>

Simulator::Simulator() {

}
Simulator::~Simulator() {}

void Simulator::update(float tpf) {
	stateManager.update(tpf);
}
void Simulator::draw() {
	// TODO pass spritebatch maybe?
	stateManager.draw();
	spriteBatch.begin(SpriteSortMode::Deferred);
	spriteBatch.draw(glm::vec2(0.f, 0.f), texture);
	spriteBatch.draw(glm::vec2(100, 100.f), texture);
	spriteBatch.draw(glm::vec2(500.f, 500.f), texture);
	spriteBatch.end();
}

void Simulator::initialize() {
	getInput().bind("Zaaryus", [](InputArgs args) {
		if (args.state == InputState::PRESSED)
			std::cout << "a pressed" << std::endl;
	}, std::vector < ITrigger* > { new KeyTrigger(SDLK_a) });
	
	spriteBatch.init();
	texture = content.load<Texture>("temp");
	effect = content.load<Effect>("shader\\basic");
	getStateManager().push(new GameplayState);
	
}
