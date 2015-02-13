#ifndef WORLD_H
#define WORLD_H
#include "Box2D\Box2D.h"
class World {
private:
	std::shared_ptr<b2World> box2dWorld;
	int32 velocityIterations;
	int32 positionIterations;
public:
	// without gravit
	World();
	// with gravity
	World(float x, float y);
	// updates physics
	void update(float tpf);

	std::shared_ptr<b2World> getBox2D();
};

#endif