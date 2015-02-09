#include "gamestates.h"
#include <iostream>


GameState::GameState() : initialized(false) {}
GameState::~GameState() {}
void GameState::init() {
	if (initialized) return;
	onInitialize();
	initialized = true;
}

GameStateManager::GameStateManager() { }
GameStateManager::~GameStateManager() {}
void GameStateManager::change(GameState* gs) { 
	pop();
	push(gs);
}
void GameStateManager::pop() {
	if (states.size() == 0) return;

	states.erase(states.end() - 1);
}
void GameStateManager::push(GameState* gs) {
	gs->init();
	states.push_back(gs);
}

void GameStateManager::update(float tpf) {
	if (states.size() == 0) {
		// TODO exit
		return;
	}

	states.back()->update(tpf);
}

void GameStateManager::draw() {
	// no need to check if states.size() == 0, because we already exit game on update()
	states.back()->draw();
}



GameplayState::GameplayState() {}
GameplayState::~GameplayState() {}

void GameplayState::onInitialize() {
	std::cout << "Gameplaystate init()" << std::endl;
}

void GameplayState::update(float tpf) {
	std::cout << "TPF " << tpf << std::endl;
}

void GameplayState::draw() {
//	std::cout << "GameplayState draw()" << std::endl;
}