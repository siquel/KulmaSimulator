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
	const b2Body* getBody() const;
	void createBody(const b2BodyDef& def);
	b2Fixture* createFixture(const b2FixtureDef& def);
protected:
	virtual void onInitialize();
	virtual void onUpdate(float tpf);
};


class PoolBallBody : public Rigidbody {
public:
	PoolBallBody(World& world);
	void onUpdate(float tpf);
};

#endif