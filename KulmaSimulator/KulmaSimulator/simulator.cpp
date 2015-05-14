#include "simulator.h"
#include <iostream>
#include "gameplay.h"
#include "gamestate\pool.h"
#include <SDL\SDL.h>
Simulator::Simulator() 
	: camera(glm::radians(45.f), static_cast<float>(Game::WINDOW_WIDTH) / Game::WINDOW_HEIGHT, 0.1f, 1500.f) {
}
Simulator::~Simulator() {}

void Simulator::update(float tpf) {
	while (!pendingActions.empty()) {
		pendingActions.front()();
		pendingActions.pop();
	}
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

void Simulator::doNextFrame(std::function<void() > action) {
	pendingActions.push(action);
}
