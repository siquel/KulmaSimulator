#include "gamestate/pool.h"
#include "component/meshrenderer.h"
#include "simulator.h"
#include "component/transform.h"

#include "entitybuilder.h"

PoolState::PoolState() : world(4.f, 0){
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
	Entity* ball = EntityBuilder::buildPoolBall(world);
	entities.addEntity(poolTable);
	entities.addEntity(ball);
	SDL_WarpMouseInWindow(Simulator::getInstance().getWindow(), Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
}