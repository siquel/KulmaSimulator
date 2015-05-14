#include "World.h"

World::World() 
	: box2dWorld(new b2World(b2Vec2(0.f, 0.f))), velocityIterations(8), positionIterations(3) {

}

World::World(float x, float y) 
	: box2dWorld(new b2World(b2Vec2(x, y))), velocityIterations(8), positionIterations(3) {

}

void World::update(float tpf) {
	box2dWorld->Step(tpf, velocityIterations, positionIterations);
}

std::shared_ptr<b2World> World::getBox2D() {
	return box2dWorld;
}

World::~World() {
	
}
