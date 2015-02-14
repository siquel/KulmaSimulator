#include "simulator.h"
#include <iostream>
#include "gameplay.h"
Simulator::Simulator() {

}
Simulator::~Simulator() {}

void Simulator::update(float tpf) {
	stateManager.update(tpf);
}
void Simulator::draw() {
	stateManager.draw(spriteBatch);
}

void Simulator::initialize() {
	spriteBatch.init();
	getStateManager().push(new GameplayState);
}
