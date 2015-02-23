#include "simulator.h"
#include <iostream>
#include "gameplay.h"
Simulator::Simulator() 
	: camera(glm::radians(25.f), static_cast<float>(Game::WINDOW_WIDTH) / Game::WINDOW_HEIGHT, 0.1f, 100.f) {
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

Camera& Simulator::getCamera() {
	return camera;
}