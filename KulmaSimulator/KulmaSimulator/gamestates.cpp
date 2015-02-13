#include "gamestates.h"
#include <iostream>
#include "simulator.h"
#include "sprite.h"
#include "inputcomponent.h"
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
	const Texture* texture = Simulator::getInstance().getContent().load<Texture>("pidgin");
	Entity* entity = new Entity();
	Sprite sprite(texture, glm::vec2(0.f, 0.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, 1.f), glm::vec2(0.f, 0.f), 0.f);
	entity->addComponent(new SpriteRenderer(*entity, sprite, 0, 0 ));
	entity->addComponent(new InputComponent(entity));
	
	entityManager.addEntity(entity);
}

void GameplayState::update(float tpf) {
	entityManager.update(tpf);
}

void GameplayState::draw(SpriteBatch& spriteBatch) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	spriteBatch.begin(SpriteSortMode::Deferred);
	
	entityManager.draw(spriteBatch);

	spriteBatch.end();
}