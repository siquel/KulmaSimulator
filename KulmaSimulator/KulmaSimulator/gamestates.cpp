#include "gamestates.h"
#include <iostream>
#include "simulator.h"

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

void GameStateManager::draw(SpriteBatch& spriteBatch) {
	// no need to check if states.size() == 0, because we already exit game on update()
	states.back()->draw(spriteBatch);
}



GameplayState::GameplayState() {}
GameplayState::~GameplayState() {}

void GameplayState::onInitialize() {
	texture = Simulator::getInstance().getContent().load<Texture>("pidgin");
}

void GameplayState::update(float tpf) {
	
}

void GameplayState::draw(SpriteBatch& spriteBatch) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	spriteBatch.begin(SpriteSortMode::Deferred);
	for (size_t i = 0; i < 1; i++) {
		spriteBatch.draw(texture, glm::vec2(100.f, 100.f));
		
	}
	spriteBatch.end();
}