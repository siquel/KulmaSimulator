#include "gameplay.h"
#include "simulator.h"
#include "sprite.h"
#include "inputcomponent.h"

GameplayState::GameplayState() {}
GameplayState::~GameplayState() {}

void GameplayState::onInitialize() {
	const Texture* texture = Simulator::getInstance().getContent().load<Texture>("pidgin");
	Entity* entity = new Entity();
	Sprite sprite(texture, glm::vec2(0.f, 0.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, 1.f), glm::vec2(0.f, 0.f), 0.f);
	entity->addComponent(new SpriteRenderer(sprite, 0, 0));
	entity->addComponent(new InputComponent());

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