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
Entity* EntityBuilder::buildPoolBall(World& world, float x, float y) {
	Entity* ball = new Entity;

	Rigidbody* body = new PoolBallBody(world);
	Mesh* ballmesh = Simulator::getInstance().getContent().load<Mesh>("mesh\\Balls\\ykone2");
	MeshRenderer* renderer = new MeshRenderer(ballmesh);

	Transform* tf = new Transform;
	tf->setPosition(glm::vec3(0.f, 0.86f, 5.f));
	tf->setScale(glm::vec3(0.25f, 0.25f, 0.25f) / 8.f);

	b2BodyDef def;
	def.fixedRotation = true;
	def.type = b2_dynamicBody;
	//def.position = b2Vec2(0.65f, 20.f);
	def.position = b2Vec2(x, y);
	body->createBody(def);

	b2FixtureDef fixtureDef;
	b2CircleShape shape;
	shape.m_radius = 0.25f / 8.f;
	fixtureDef.shape = &shape;
	body->createFixture(fixtureDef);

	ball->addComponent(tf);
	ball->addComponent(renderer);
	ball->addComponent(body);
	body->enable();
	return ball;
}

Entity** EntityBuilder::buildPooBallTriangle(World& world) {
	// triangle
	Entity** balls = new Entity*[15];
	float r = 0.25f / 8.f;
	float d = r * 2.f;
	float y = 0.f;
	float x = 0.f;
	float currentx = x - r/2.f;
	x = currentx;
	balls[0] = EntityBuilder::buildPoolBall(world, 0.f, 0.f);
	y += d;
	for (size_t i = 1; i < 15; i++) {
		if (i == 3) {
			y += d;
			x = currentx -= r/2.f;
		}
		else if (i == 6) {
			y += d;
			x = currentx -= r / 2.f;
		}
		else if (i == (1 + 2 + 3)) {
			y += d;
			x = currentx -= r / 2.f;
		}
		else if (i == (1 + 2 + 3 + 4)) {
			y += d;
			x = currentx -= r / 2.f;
		}
		
		balls[i] = EntityBuilder::buildPoolBall(world, x, y);
		x += r;
	}
	return balls;
}