#include "gameplay.h"
#include "simulator.h"
#include "sprite.h"
#include "component/inputcomponent.h"
#include "component/rigidbody.h"
#include "component/meshrenderer.h"
#include "component/transform.h"
GameplayState::GameplayState() : world(0.f, 0.f) {}
GameplayState::~GameplayState() {}

void GameplayState::onInitialize() {
	const Texture* texture = Simulator::getInstance().getContent().load<Texture>("pidgin");
	Entity* entity = new Entity();
	Sprite sprite(texture, glm::vec2(0.f, 0.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec2(1.f, 1.f), glm::vec2(0.f, 0.f), 0.f);
	entity->addComponent(new SpriteRenderer(sprite, 0, 0));
	entity->addComponent(new Transform());
	entity->getComponent<Transform>()->setPosition(glm::vec3(0.f, 0.f, 0.f));
	entity->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\Pooli\\table")));
	entity->addComponent(new InputComponent());
	entity->addComponent(new Rigidbody(world));

	entityManager.addEntity(entity);
	Entity* asd = new Entity();

	
	asd->addComponent(new Transform());
	asd->getComponent<Transform>()->setPosition(glm::vec3(0.f, 0.f, 0.f));
	//asd->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\Pooli\\table")));
	//entityManager.addEntity(asd);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Mesh* mesh = Simulator::getInstance().getContent().load<Mesh>("mesh\\cube");
	SDL_WarpMouseInWindow(Simulator::getInstance().getWindow(), Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
}

void GameplayState::update(float tpf) {
	world.update(tpf);
	entityManager.update(tpf);
	Simulator::getInstance().getCamera().update(tpf);
}

void GameplayState::draw(SpriteBatch& spriteBatch) {
	Font* font = Simulator::getInstance().getContent().load<Font>("font\\VeronaScript");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*spriteBatch.begin(SpriteSortMode::Deferred);
	font->drawString(spriteBatch, std::string("Olipa kerran Pidgin :D\nJoka sai ohjelmoinnista :D\nKakkosen :D::D:\nlel"), glm::vec2(500.f, 500.f), glm::vec4(1.f, 1.f, 1.f, 1.f), glm::radians(0.0f), glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f));
	
	spriteBatch.end();*/
	entityManager.draw(spriteBatch);
}