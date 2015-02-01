#include "simulator.h"
#include <iostream>


Simulator::Simulator() {}
Simulator::~Simulator() {}

void Simulator::update() {}
void Simulator::draw() { }

void Simulator::initialize() {
	getInput().bind("Zaaryus", [](InputArgs* args) {
		std::cout << "a pressed" << std::endl;
	}, std::vector < ITrigger* > { new KeyTrigger(SDLK_a) });
	Texture* tx = content.load<Texture>("temp");
}
