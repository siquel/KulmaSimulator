#include "entitybuilder.h"
#include "Entity.h"
#include "component\rigidbody.h"
#include "simulator.h"
#include "component\meshrenderer.h"
#include "component\transform.h"
#include "Box2D\Box2D.h"
Entity* EntityBuilder::buildPoolTable(World& world) {
	Entity* table = new Entity;

	Rigidbody* body = new Rigidbody(world);
	Mesh* tableMesh = Simulator::getInstance().getContent().load<Mesh>("mesh\\Pooli\\table");
	MeshRenderer* renderer = new MeshRenderer(tableMesh);

	Transform* tf = new Transform;
	tf->setPosition(glm::vec3(0.f, 0.f, 5.f));


	b2BodyDef def;
	def.fixedRotation = true;
	def.type = b2_staticBody;
	body->createBody(def);

	b2FixtureDef fixtureDef;
	b2PolygonShape box;
	box.SetAsBox(3 / 2.f, 5 / 2.f);
	fixtureDef.shape = &box;
	body->createFixture(fixtureDef);

	table->addComponent(tf);
	table->addComponent(renderer);
	table->addComponent(body);
	body->enable();
	return table;
}

Entity* EntityBuilder::buildPoolBall(World& world) {
	Entity* ball = new Entity;

	Rigidbody* body = new PoolBallBody(world);
	Mesh* ballmesh = Simulator::getInstance().getContent().load<Mesh>("mesh\\Balls\\ykone2");
	MeshRenderer* renderer = new MeshRenderer(ballmesh);

	Transform* tf = new Transform;
	tf->setPosition(glm::vec3(0.f, 1.f, 5.f));
	tf->setScale(glm::vec3(0.25f, 0.25f, 0.25f));

	b2BodyDef def;
	def.fixedRotation = true;
	def.type = b2_dynamicBody;
	def.position = b2Vec2(0.f, 100.f);
	body->createBody(def);

	b2FixtureDef fixtureDef;
	b2CircleShape shape;
	shape.m_radius = 1.f;
	fixtureDef.shape = &shape;
	body->createFixture(fixtureDef);

	ball->addComponent(tf);
	ball->addComponent(renderer);
	ball->addComponent(body);
	body->enable();
	return ball;
}