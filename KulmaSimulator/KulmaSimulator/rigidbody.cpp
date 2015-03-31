#include "component/rigidbody.h"
#include "Entity.h"
#include "component\transform.h"
#include <iostream>
Rigidbody::Rigidbody(World& world) : Component(0), world(world.getBox2D()) {
	
}

Rigidbody::~Rigidbody() {}

void Rigidbody::onInitialize() {

}

const b2Body* Rigidbody::getBody() const {
	return body;
}

void Rigidbody::createBody(const b2BodyDef& def) {
	body = world.lock().get()->CreateBody(&def);
}

b2Fixture* Rigidbody::createFixture(const b2FixtureDef& def) {
	return body->CreateFixture(&def);
}

void Rigidbody::onUpdate(float tpf) {}


PoolBallBody::PoolBallBody(World& world) : Rigidbody(world) {

}
void PoolBallBody::onUpdate(float tpf) {
	Transform* tf = getOwner()->getComponent<Transform>();
	const b2Transform& tx = getBody()->GetTransform();
	tf->setPosition(glm::vec3(tx.p.x, 1.5f, tx.p.y));
	std::cout << tx.p.x << " " << tx.p.y << std::endl;
}