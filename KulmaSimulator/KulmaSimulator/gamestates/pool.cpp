#include "gamestate/pool.h"
#include "component/meshrenderer.h"
#include "simulator.h"
#include "component/transform.h"
#include "component/debugcue.h"
#include "entitybuilder.h"

PoolState::PoolState() : world(0.f, -0.f){
	debugdraw.SetFlags(b2Draw::e_shapeBit);
	world.getBox2D()->SetDebugDraw(&debugdraw);
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
	debugdraw.doDraw();
	
}

void PoolState::onInitialize() {

	Entity* poolTable = EntityBuilder::buildPoolTable(world);
	Entity** balls = EntityBuilder::buildPooBallTriangle(world);
	entities.addEntity(poolTable);
	for (size_t i = 0; i < 15; i++) {
		entities.addEntity(balls[i]);
	}
	Entity* cueball = EntityBuilder::buildPoolBall(world, 0.f, -1.f);
	cueball->addComponent(new DebugCueBall);
	entities.addEntity(cueball);
	SDL_WarpMouseInWindow(Simulator::getInstance().getWindow(), Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
}