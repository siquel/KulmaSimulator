#include "entitybuilder.h"
#include "Entity.h"
#include "component\rigidbody.h"
#include "simulator.h"
#include "component\meshrenderer.h"
#include "component\transform.h"
#include "Box2D\Box2D.h"
#include "EntityManager.h"
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
	//fixtureDef.restitution = 0.5f;
	fixtureDef.friction = 0.2f;
	fixtureDef.density = 0;
	b2PolygonShape box;
	// bottom
	box.SetAsBox(0.6f, 0.1f, -b2Vec2(0.f, top/2.f + 0.01f), 0.f);
	fixtureDef.shape = &box;
	body->createFixture(fixtureDef);

	b2CircleShape hole;
	hole.m_radius = 0.25f / 6.f;

	// upper
	box.SetAsBox(w, 0.1f, b2Vec2(0.f, top/2.f + 0.01f), 0.f);
	fixtureDef.shape = &box;
	body->createFixture(fixtureDef);
	
	// right
	box.SetAsBox(0.1f, top / 2.f, -b2Vec2(w + 0.18f, 0.f), 0.f);
	fixtureDef.shape = &box;
	body->createFixture(fixtureDef);
	
	// left
	box.SetAsBox(0.1f, top / 2.f, b2Vec2(w + 0.18f, 0.f), 0.f);
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
	tf->setPosition(glm::vec3(0.f, 0.83f, 5.f));
	tf->setScale(glm::vec3(0.25f, 0.25f, 0.25f) / 8.f);

	b2BodyDef def;
	def.fixedRotation = false;
	def.type = b2_dynamicBody;
	def.bullet = true;
	def.angularDamping = 0.7f;
	def.linearDamping = 0.4f;
	def.allowSleep = false;
	//def.position = b2Vec2(0.65f, 20.f);
	def.position = b2Vec2(x, y);
	body->createBody(def);

	b2FixtureDef fixtureDef;
	b2CircleShape shape;
	shape.m_radius = 0.25f / 8.f;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.7f;
	fixtureDef.restitution = 0.3f;
	fixtureDef.density = 58.474822f;
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

Entity* EntityBuilder::createWall(const glm::vec3& pos, const glm::vec3& scale) {
	Entity* wall = new Entity;
	Transform* walltf = new Transform;
	walltf->setPosition(pos);
	walltf->setScale(scale);
	wall->addComponent(walltf);
	wall->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\cube")));
	return wall;
}

Entity* EntityBuilder::createTableGroup(const glm::vec3& pos, float rotation, const glm::vec3& axis) {
	Entity* tablegroup = new Entity;
	Transform* tablegrptf = new Transform;
	tablegrptf->rotate(glm::radians(rotation), axis);
	tablegrptf->setPosition(pos);
	tablegroup->addComponent(tablegrptf);
	tablegroup->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\table\\tablegroup")));
	return tablegroup;
}

Entity* EntityBuilder::buildKulma(EntityManager& entityManager) {
	float width = 10;
	float height = 15.f;

	Entity* kulma = new Entity;

	std::vector<Entity*> entities;

	Entity* floor = new Entity;
	Transform* floortf = new Transform;
	floortf->setScale(glm::vec3(width, 1.f, height));
	floortf->setPosition(glm::vec3(0.f, -1.f, 0.f));
	floor->addComponent(floortf);
	floor->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\cube")));
	entities.push_back(floor);

	Entity* leftWall = EntityBuilder::createWall(glm::vec3(width + 1.f, 2.f, 0.f), glm::vec3(1.f, 5.f, height));
	Entity* rightWall = EntityBuilder::createWall(glm::vec3(-(width + 1.f), 2.f, 0.f), glm::vec3(1.f, 5.f, height));
	Entity* topWall = EntityBuilder::createWall(glm::vec3(0.f, 2.f, height + 1), glm::vec3(width, 5.f, 1.f));
	Entity* bottomWall = EntityBuilder::createWall(glm::vec3(0.f, 2.f, -(height + 1)), glm::vec3(width, 5.f, 1.f));
	entities.push_back(leftWall);
	entities.push_back(rightWall);
	entities.push_back(topWall);
	entities.push_back(bottomWall);

	for (size_t i = 1; i <= 4; ++i) {
		entities.push_back(createTableGroup(glm::vec3(width - 2.5f * i, 0.f, height - 2.f), 90.f, glm::vec3(0, 1, 0)));
	}
	for (size_t i = 0; i < entities.size(); i++) {
		kulma->addChild(entities[i]);
		entityManager.addEntity(entities[i]);
	}
	return kulma;
}