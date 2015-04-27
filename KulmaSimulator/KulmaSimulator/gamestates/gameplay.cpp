#include "gameplay.h"
#include "simulator.h"
#include "sprite.h"
#include "component/inputcomponent.h"
#include "component/rigidbody.h"
#include "component/meshrenderer.h"
#include "component/transform.h"
#include "component/player_controller.h"
#include "entitybuilder.h"
GameplayState::GameplayState() : world(0.f, 0.f) {}
GameplayState::~GameplayState() {}

void GameplayState::onInitialize() {

	Entity* player = new Entity;
	player->addComponent(new Transform);
	player->addComponent(new PlayerController);
	entityManager.addEntity(player);

	Entity* table = new Entity();
	table->addComponent(new Transform());
	table->getComponent<Transform>()->setPosition(glm::vec3(5.f, 0.f, 5.f));
	table->getComponent<Transform>()->rotate(glm::radians(90.f), glm::vec3(0.f,1.f,0.f));
	table->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\Pooli\\table")));
	table->addComponent(new Rigidbody(world));
	entityManager.addEntity(table);

	Entity* kulma = EntityBuilder::buildKulma(entityManager);

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