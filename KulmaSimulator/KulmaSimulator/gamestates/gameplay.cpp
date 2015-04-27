#include "gameplay.h"
#include "simulator.h"
#include "sprite.h"
#include "component/inputcomponent.h"
#include "component/rigidbody.h"
#include "component/meshrenderer.h"
#include "component/transform.h"
#include "component/player_controller.h"
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

	float width = 10;
	float height = 15.f;

	Entity* floor = new Entity;
	Transform* floortf = new Transform;
	floortf->setScale(glm::vec3(width, 1.f, height));
	floortf->setPosition(glm::vec3(0.f, -1.f, 0.f));
	floor->addComponent(floortf);
	floor->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\cube")));
	entityManager.addEntity(floor);

	Entity* leftWall = new Entity;
	Transform* walltf = new Transform;
	walltf->setPosition(glm::vec3(width + 1.f, 2.f, 0.f));
	walltf->setScale(glm::vec3(1.f, 5.f, height));
	leftWall->addComponent(walltf);
	leftWall->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\cube")));
	entityManager.addEntity(leftWall);

	Entity* rightWall = new Entity;
	Transform* rightwalltf = new Transform;
	rightwalltf->setPosition(glm::vec3(-(width + 1.f), 2.f, 0.f));
	rightwalltf->setScale(glm::vec3(1.f, 5.f, height));
	rightWall->addComponent(rightwalltf);
	rightWall->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\cube")));
	entityManager.addEntity(rightWall);
	
	Entity* topWall = new Entity;
	Transform* topWalltf = new Transform;
	topWalltf->setPosition(glm::vec3(0.f, 2.f, height + 1));
	topWalltf->setScale(glm::vec3(width, 5.f, 1.f));
	topWall->addComponent(topWalltf);
	topWall->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\cube")));
	entityManager.addEntity(topWall);

	Entity* bottomWall = new Entity;
	Transform* bottoWalltf = new Transform;
	bottoWalltf->setPosition(glm::vec3(0.f, 2.f, -(height + 1)));
	bottoWalltf->setScale(glm::vec3(width, 5.f, 1.f));
	bottomWall->addComponent(bottoWalltf);
	bottomWall->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\cube")));
	entityManager.addEntity(bottomWall);

	Entity* tablegroup = new Entity;
	Transform* tablegrptf = new Transform;
	tablegrptf->rotate(glm::radians(90.f), glm::vec3(0, 1, 0));
	tablegrptf->setPosition(glm::vec3(width - 2.f, 0.f, height - 2.f));
	tablegroup->addComponent(tablegrptf);
	tablegroup->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\table\\tablegroup")));
	entityManager.addEntity(tablegroup);

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