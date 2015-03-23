#include "gamestate/pool.h"
#include "component/meshrenderer.h"
#include "simulator.h"
#include "component/transform.h"
PoolState::PoolState() {

}

PoolState::~PoolState() {
	
}

void PoolState::update(float tpf) {
	entities.update(tpf);
	Simulator::getInstance().getCamera().update(tpf);
}

void PoolState::draw(SpriteBatch& sb) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	entities.draw(sb);
}

void PoolState::onInitialize() {
	Entity* poolTable = new Entity();
	ContentManager& content = Simulator::getInstance().getContent();
	Mesh* table = content.load<Mesh>("mesh\\table\\tablegroup");
	poolTable->addComponent(new MeshRenderer(table));
	Transform* t = new Transform;
	t->setPosition(glm::vec3(0.f, 0.f, 5.f));
	//t->rotate(90.f, glm::vec3(0.f, 1.f, 0.f));
	poolTable->addComponent(t);
	entities.addEntity(poolTable);
	SDL_WarpMouseInWindow(Simulator::getInstance().getWindow(), Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
}