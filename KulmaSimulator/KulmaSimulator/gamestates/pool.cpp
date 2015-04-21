#include "gamestate/pool.h"
#include "component/meshrenderer.h"
#include "simulator.h"
#include "component/transform.h"
#include "entitybuilder.h"
#include "component/poolstick.h"

PoolState::PoolState() : world(0.f, -0.f){
	
}

PoolState::~PoolState() {
	
}

void PoolState::update(float tpf) {
	world.update(tpf);
	entities.update(tpf);
	Simulator::getInstance().getCamera().update(tpf);
}

void PoolState::draw(SpriteBatch& sb) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	entities.draw(sb);
	world.getBox2D()->DrawDebugData();
}

void PoolState::onInitialize() {
	ContentManager& content = Simulator::getInstance().getContent();
	Entity* poolTable = EntityBuilder::buildPoolTable(world);
	Entity** balls = EntityBuilder::buildPooBallTriangle(world);
	entities.addEntity(poolTable);
	for (size_t i = 0; i < 15; i++) {
		entities.addEntity(balls[i]);
	}

	Entity* cueball = EntityBuilder::buildPoolBall(world, 0.f, -1.f);
	entities.addEntity(cueball);

	Entity* player = new Entity();
	player->addComponent(new PoolStick(cueball));
	Transform* tf = new Transform;
	tf->rotate(glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
	player->addComponent(tf);
	player->addComponent(new MeshRenderer(content.load<Mesh>("mesh\\maila\\keppi")));
	entities.addEntity(player);

	SDL_WarpMouseInWindow(Simulator::getInstance().getWindow(), Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
}