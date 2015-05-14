#include "component/rigidbody.h"
#include "Entity.h"
#include "component\transform.h"
#include <iostream>
#include "collision_listener.h"
Rigidbody::Rigidbody(World& world) : Component(0), world(world.getBox2D()) {
	
}

Rigidbody::~Rigidbody() {
	world.lock().get()->DestroyBody(body);
}

void Rigidbody::onInitialize() {

}

b2Body* Rigidbody::getBody() const {
	return body;
}

void Rigidbody::createBody(const b2BodyDef& def) {
	body = world.lock().get()->CreateBody(&def);
	body->SetUserData(getOwner());
}

b2Fixture* Rigidbody::createFixture(const b2FixtureDef& def) {
	b2Fixture* fixture = body->CreateFixture(&def);
	fixture->SetUserData(getOwner());
	return fixture;
}

void Rigidbody::onUpdate(float tpf) {}


DynamicBody::DynamicBody(World& world) : Rigidbody(world) {

}
void DynamicBody::onUpdate(float tpf) {
	Transform* tf = getOwner()->getComponent<Transform>();
	const b2Transform& tx = getBody()->GetTransform();
	tf->setPosition(glm::vec3(tx.p.x, tf->getPosition().y, tx.p.y));
	//std::cout << tx.p.x << " " << tx.p.y << std::endl;
}

DynamicBody::~DynamicBody() {

}


CircleCollider::CircleCollider(World& world, float r, const glm::vec2& pos /*= glm::vec2(0, 0)*/) 
	: world(world.getBox2D()), radius(r), pos(pos) {
}

void CircleCollider::onInitialize() {
	b2BodyDef def;
	Transform* tx = getOwner()->getComponent<Transform>();
	def.position = b2Vec2(tx->getPosition().x, tx->getPosition().z);
	def.type = b2_staticBody;
	body = world.lock().get()->CreateBody(&def);

	b2FixtureDef fixdef;
	b2CircleShape shape;
	shape.m_p.Set(pos.x, pos.y);
	shape.m_radius = radius;

	fixdef.shape = &shape;
	// hax?
	fixdef.isSensor = true;
	fixdef.userData = getOwner();
	body->CreateFixture(&fixdef);
}

void CircleCollider::onUpdate(float tpf) {

}

void CircleCollider::setCollisionListener(CollisionListener* listener) {
	ContactListener* cl = static_cast<ContactListener*>(world.lock().get()->GetContactManager().m_contactListener);
	cl->addListener(listener);
}

void CircleCollider::removeCollisionListener(CollisionListener* listener) {
	ContactListener* cl = static_cast<ContactListener*>(world.lock().get()->GetContactManager().m_contactListener);
	cl->removeListener(listener);
}
