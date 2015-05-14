#include "engine/gamestates.h"
#include <iostream>
#include "simulator.h"
#include "sprite.h"
#include "component/inputcomponent.h"
GameState::GameState() : initialized(false) {}
GameState::~GameState() {}
void GameState::init() {
	if (initialized) return;
	onInitialize();
	initialized = true;
}

void GameState::unload() {
	if (initialized) {
		initialized = false;
		onUnload();
	}
}

void GameState::onUnload() {

}

GameStateManager::GameStateManager() { }
GameStateManager::~GameStateManager() {}
void GameStateManager::change(GameState* gs) { 
	pop();
	push(gs);
}
void GameStateManager::pop() {
	if (states.size() == 0) return;
	states.back()->unload();
	delete states.back();
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

void GameStateManager::draw(SpriteBatch& spriteBatch) {
	// no need to check if states.size() == 0, because we already exit game on update()
	states.back()->draw(spriteBatch);
}