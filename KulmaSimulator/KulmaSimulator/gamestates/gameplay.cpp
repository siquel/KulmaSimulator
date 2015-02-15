#include "gameplay.h"
#include "simulator.h"
#include "sprite.h"
#include "inputcomponent.h"
#include "rigidbody.h"

GameplayState::GameplayState() : world(0.f, 0.f) {}
GameplayState::~GameplayState() {}

void GameplayState::onInitialize() {
	const Texture* texture = Simulator::getInstance().getContent().load<Texture>("pidgin");
	Entity* entity = new Entity();
	Sprite sprite(texture, glm::vec2(0.f, 0.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, 1.f), glm::vec2(0.f, 0.f), 0.f);
	entity->addComponent(new SpriteRenderer(sprite, 0, 0));
	entity->addComponent(new InputComponent());
	entity->addComponent(new Rigidbody(world));
	entityManager.addEntity(entity);

	Font* font = Simulator::getInstance().getContent().load<Font>("font\\VeronaScript");
}

void GameplayState::update(float tpf) {
	world.update(tpf);
	entityManager.update(tpf);
	
}

void GameplayState::draw(SpriteBatch& spriteBatch) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	spriteBatch.begin(SpriteSortMode::Deferred);

	entityManager.draw(spriteBatch);

	spriteBatch.end();
}