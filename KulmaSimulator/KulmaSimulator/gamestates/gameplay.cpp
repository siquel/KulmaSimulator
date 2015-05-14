#include "gameplay.h"
#include "simulator.h"
#include "sprite.h"
#include "component/inputcomponent.h"
#include "component/meshrenderer.h"
#include "component/transform.h"
#include "entitybuilder.h"
GameplayState::GameplayState() : world(0.f, 0.f) {
	world.getBox2D()->SetContactListener(&collisionListener);
}
GameplayState::~GameplayState() {}

void GameplayState::onInitialize() {

	Entity* player = EntityBuilder::buildPlayer(world);
	entityManager.addEntity(player);

	Entity* kulma = EntityBuilder::buildKulma(entityManager, world);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	SDL_WarpMouseInWindow(Simulator::getInstance().getWindow(), Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
}

void GameplayState::update(float tpf) {
	world.update(tpf);
	entityManager.update(tpf);
	Simulator::getInstance().getCamera().update(tpf);
}

void GameplayState::draw(SpriteBatch& spriteBatch) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	entityManager.draw(spriteBatch);
}

void GameplayState::onUnload() {
	entityManager.clear();
}
