#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include "Component.h"
#include "Box2D\Box2D.h"
#include "World.h"
class Rigidbody : public Component {
private:
	b2Body* body;
	std::weak_ptr<b2World> world;
public:
	Rigidbody(World& world);
	~Rigidbody();
protected:
	void onInitialize();
};

#endif