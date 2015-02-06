#include "simulator.h"
#include <iostream>

Simulator::Simulator() {

}
Simulator::~Simulator() {}

void Simulator::update() {}
void Simulator::draw() { 
	spriteBatch.begin(SpriteSortMode::Deferred);
	spriteBatch.draw(pmath::Vec2f(0.f, 0.f), texture);
	spriteBatch.draw(pmath::Vec2f(-100.f, -100.f), texture);
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
