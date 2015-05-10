#include "entitybuilder.h"
#include "Entity.h"
#include "component\rigidbody.h"
#include "simulator.h"
#include "component\meshrenderer.h"
#include "component\transform.h"
#include "Box2D\Box2D.h"
#include "EntityManager.h"
#include "component/player_controller.h"
#include "component/rigidbody.h"
Entity* EntityBuilder::buildPoolTable(World& world) {
	Entity* table = new Entity;

	Rigidbody* body = new DynamicBody(world);
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

	Rigidbody* body = new DynamicBody(world);
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

Entity* EntityBuilder::createWall(World& world, const glm::vec3& pos, const glm::vec3& scale) {
	Entity* wall = new Entity;
	Transform* walltf = new Transform;
	Rigidbody* body = new Rigidbody(world);
	walltf->setPosition(pos);
	walltf->setScale(scale);
	wall->addComponent(walltf);
	wall->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\cube")));
	wall->addComponent(body);
	body->enable();

	b2BodyDef bodydef;
	bodydef.type = b2_staticBody;
	bodydef.position = b2Vec2(pos.x, pos.z);
	body->createBody(bodydef);

	b2PolygonShape shape;
	shape.SetAsBox(scale.x , scale.z );
	b2FixtureDef fixdef;
	fixdef.shape = &shape;
	body->createFixture(fixdef);

	return wall;
}

Entity* EntityBuilder::createTableGroup(World& world, const glm::vec3& pos, float rotation, const glm::vec3& axis) {
	Entity* tablegroup = new Entity;
	Transform* tablegrptf = new Transform;
	tablegrptf->rotate(glm::radians(rotation), axis);
	tablegrptf->setPosition(pos);
	tablegroup->addComponent(tablegrptf);
	tablegroup->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\table\\tablegroup")));
	Rigidbody* body = new Rigidbody(world);
	tablegroup->addComponent(body);
	body->enable();
	b2BodyDef bodydef;
	bodydef.type = b2_staticBody;
	bodydef.position = b2Vec2(pos.x, pos.z);
	body->createBody(bodydef);

	b2FixtureDef fixdef;
	b2PolygonShape shape;
	shape.SetAsBox(0.9f, 0.8f);
	fixdef.shape = &shape;
	body->createFixture(fixdef);

	return tablegroup;
}

Entity* EntityBuilder::buildKulma(EntityManager& entityManager, World& world) {
	float width = 10;
	float height = 15.f;


	ContentManager& content = Simulator::getInstance().getContent();

	Entity* kulma = new Entity;

	std::vector<Entity*> entities;

	Entity* floor = new Entity;
	Transform* floortf = new Transform;
	floortf->setScale(glm::vec3(width, 1.f, height));
	floortf->setPosition(glm::vec3(0.f, -1.f, 0.f));
	floor->addComponent(floortf);
	floor->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\cube")));
	floor->getComponent<MeshRenderer>()->setTexture(content.load<Texture>("tex\\floor"));
	entities.push_back(floor);

	Entity* leftWall = EntityBuilder::createWall(world, glm::vec3(width + 1.f, 2.f, 0.f), glm::vec3(1.f, 5.f, height));
	Entity* rightWall = EntityBuilder::createWall(world, glm::vec3(-(width + 1.f), 2.f, 0.f), glm::vec3(1.f, 5.f, height));
	Entity* topWall = EntityBuilder::createWall(world, glm::vec3(0.f, 2.f, height + 1), glm::vec3(width, 5.f, 1.f));
	Entity* bottomWall = EntityBuilder::createWall(world, glm::vec3(0.f, 2.f, -(height + 1)), glm::vec3(width, 5.f, 1.f));
	entities.push_back(leftWall);
	entities.push_back(rightWall);
	entities.push_back(topWall);
	entities.push_back(bottomWall);

	Entity* table = buildStandardPoolTable(world, glm::vec3(width - 3.f, 0.f, height - 6.f), 90.f, glm::vec3(0.f, 1.f, 0.f));
	entities.push_back(table);

	Entity* door = new Entity;
	door->addComponent(new Transform);
	door->addComponent(new MeshRenderer(content.load<Mesh>("mesh\\counter\\counter")));
	entities.push_back(door);

	for (size_t i = 1; i <= 4; ++i) {
		entities.push_back(createTableGroup(world, glm::vec3(width - 2.5f * i, 0.f, height - 1.3f), 90.f, glm::vec3(0, 1, 0)));
	}

	for (size_t i = 1; i <= 2; ++i) {
		entities.push_back(createTableGroup(world, glm::vec3(width - 1.5f, 0.f, height - 9.f - (2.f * i)), 0.f, glm::vec3(0, 1, 0)));
	}
	// wc
	float start = width - (5 * 2.5f);
	entities.push_back(createWall(world, glm::vec3(start, 2.f, height - 3.f), glm::vec3(0.5f, 5.f, 5.f)));

	for (size_t i = 0; i < entities.size(); i++) {
		kulma->addChild(entities[i]);
		entityManager.addEntity(entities[i]);
	}
	return kulma;
}

Entity* EntityBuilder::buildPlayer(World& world) {
	Entity* player = new Entity;
	player->addComponent(new Transform);
	player->addComponent(new PlayerController);

	CircleCollider* fov = new CircleCollider(world, 2.f);
	player->addComponent(fov);
	fov->enable();

	Rigidbody* body = new DynamicBody(world);
	player->addComponent(body);
	body->enable();

	b2BodyDef bodydef;
	bodydef.type = b2_dynamicBody;
	bodydef.fixedRotation = true;
	bodydef.angularDamping = 10.f;
	bodydef.linearDamping = 10.f;
	body->createBody(bodydef);

	b2CircleShape shape;
	shape.m_radius = 0.5f;
	b2FixtureDef fixdef;
	fixdef.friction = 0.8f;
	fixdef.density = 1;
	fixdef.shape = &shape;
	body->createFixture(fixdef);
	return player;
}

Entity* EntityBuilder::buildStandardPoolTable(World& world, const glm::vec3& pos, const float rotation, const glm::vec3& axis) {
	Entity* table = new Entity();
	table->addComponent(new Transform());
	table->getComponent<Transform>()->setPosition(pos);
	table->getComponent<Transform>()->rotate(glm::radians(rotation), axis);
	table->addComponent(new MeshRenderer(Simulator::getInstance().getContent().load<Mesh>("mesh\\Pooli\\table")));

	Rigidbody* body = new Rigidbody(world);
	table->addComponent(body);
	body->enable();
	b2BodyDef bodydef;
	bodydef.type = b2_staticBody;
	bodydef.position = b2Vec2(pos.x, pos.z);
	body->createBody(bodydef);
	
	b2PolygonShape shape;
	shape.SetAsBox(1.5f, 1.f);
	b2FixtureDef fixdef;
	fixdef.shape = &shape;
	body->createFixture(fixdef);

	return table;
}
