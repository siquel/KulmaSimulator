#include "entitybuilder.h"
#include "Entity.h"
#include "component\rigidbody.h"
#include "simulator.h"
#include "component\meshrenderer.h"
#include "component\transform.h"
#include "Box2D\Box2D.h"
Entity* EntityBuilder::buildPoolTable(World& world) {
	Entity* table = new Entity;

	Rigidbody* body = new PoolBallBody(world);
	Mesh* tableMesh = Simulator::getInstance().getContent().load<Mesh>("mesh\\Pooli\\table");
	MeshRenderer* renderer = new MeshRenderer(tableMesh);

	Transform* tf = new Transform;
	tf->setPosition(glm::vec3(0.f, 0.f, 0.f));


	b2BodyDef def;
	def.fixedRotation = true;
	def.type = b2_staticBody;
	body->createBody(def);

	float top = 3.05f;
	float w = 0.65f;
	float halfwidth = 1.f;

	b2FixtureDef fixtureDef;
	b2PolygonShape box;
	// bottom
	box.SetAsBox(w, 0.1f, -b2Vec2(0.f, top/2.f), 0.f);
	fixtureDef.shape = &box;
	body->createFixture(fixtureDef);

	// upper
	box.SetAsBox(w, 0.1f, b2Vec2(0.f, top/2.f - 0.2f), 0.f);
	fixtureDef.shape = &box;
	body->createFixture(fixtureDef);
	
	// left
	box.SetAsBox(0.1f, top / 2.f, -b2Vec2(w + 0.2f, 0.f), 0.f);
	fixtureDef.shape = &box;
	body->createFixture(fixtureDef);
	
	// right
	box.SetAsBox(0.1f, top / 2.f, b2Vec2(w + 0.2f, 0.f), 0.f);
	fixtureDef.shape = &box;
	body->createFixture(fixtureDef);

	table->addComponent(tf);
	table->addComponent(renderer);
	table->addComponent(body);
	body->enable();
	return table;
}
static float i = 1.f;
Entity* EntityBuilder::buildPoolBall(World& world) {
	Entity* ball = new Entity;

	Rigidbody* body = new PoolBallBody(world);
	Mesh* ballmesh = Simulator::getInstance().getContent().load<Mesh>("mesh\\Balls\\ykone2");
	MeshRenderer* renderer = new MeshRenderer(ballmesh);

	Transform* tf = new Transform;
	tf->setPosition(glm::vec3(0.f, 0.86f, 5.f));
	tf->setScale(glm::vec3(0.25f, 0.25f, 0.25f) / 4.f);

	b2BodyDef def;
	def.fixedRotation = true;
	def.type = b2_dynamicBody;
	//def.position = b2Vec2(0.65f, 20.f);
	def.position = b2Vec2(-0.f, 0.f);
	body->createBody(def);

	b2FixtureDef fixtureDef;
	b2CircleShape shape;
	shape.m_radius = 0.25f / 4.f;
	fixtureDef.shape = &shape;
	body->createFixture(fixtureDef);

	ball->addComponent(tf);
	ball->addComponent(renderer);
	ball->addComponent(body);
	body->enable();
	return ball;
}