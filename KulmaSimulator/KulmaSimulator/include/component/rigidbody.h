#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include "Component.h"
#include "Box2D\Box2D.h"
#include "World.h"
#include "GLM.h"
class CollisionListener;
class Rigidbody : public Component {
private:
	b2Body* body;
	std::weak_ptr<b2World> world;
public:
	Rigidbody(World& world);
	virtual ~Rigidbody();
	b2Body* getBody() const;
	void createBody(const b2BodyDef& def);
	b2Fixture* createFixture(const b2FixtureDef& def);
protected:
	virtual void onInitialize();
	virtual void onUpdate(float tpf);
};


class DynamicBody : public Rigidbody {
public:
	DynamicBody(World& world);
	~DynamicBody();
	void onUpdate(float tpf);
};

class CircleCollider : public Component {
private:
	b2Body* body;
	std::weak_ptr<b2World> world;
	float radius;
	glm::vec2 pos;
public:
	CircleCollider(World& world, float r, const glm::vec2& pos = glm::vec2(0, 0));
	void setCollisionListener(CollisionListener* listener);
	void removeCollisionListener(CollisionListener* listener);
protected:
	void onInitialize() override;
	void onUpdate(float tpf) override;
};

#endif