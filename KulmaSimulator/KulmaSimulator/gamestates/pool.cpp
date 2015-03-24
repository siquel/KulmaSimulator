#include "gamestate/pool.h"
#include "component/meshrenderer.h"
#include "simulator.h"
#include "component/transform.h"
#include "component/rigidbody3d.h"

PoolState::PoolState() {
	debugdraw.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
}

PoolState::~PoolState() {
	delete world;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
}

void PoolState::update(float tpf) {
	world->stepSimulation(1 / 60.f, 10);
	entities.update(tpf);
	Simulator::getInstance().getCamera().update(tpf);
	world->debugDrawWorld();

}

void PoolState::draw(SpriteBatch& sb) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	entities.draw(sb);
	debugdraw.draw();
}

void PoolState::onInitialize() {


	broadphase = new btDbvtBroadphase();

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	solver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	world->setGravity(btVector3(0, -9.8, 0));
	world->setDebugDrawer(&debugdraw);
	Entity* poolTable = new Entity();
	ContentManager& content = Simulator::getInstance().getContent();
	Mesh* table = content.load<Mesh>("mesh\\Pooli\\table");
	poolTable->addComponent(new MeshRenderer(table));
	Rigidbody3D* rigidbody = new Rigidbody3D();
	poolTable->addComponent(rigidbody);
	rigidbody->enable();
	world->addRigidBody(rigidbody->getBody());
	Transform* t = new Transform;
	t->setPosition(glm::vec3(0.f, 0.f, 5.f));
	//t->rotate(90.f, glm::vec3(0.f, 1.f, 0.f));
	poolTable->addComponent(t);
	entities.addEntity(poolTable);


	Entity* poolBall = new Entity();
	Mesh* ball = content.load<Mesh>("mesh\\Balls\\ykone2");
	poolBall->addComponent(new MeshRenderer(ball));
	Rigidbody3D* bllbody = new Rigidbody3D();
	poolBall->addComponent(bllbody);
	bllbody->enable();

	//bllbody->getBody()->setMassProps(0.1f, btVector3(0, 0, 0));
	world->addRigidBody(bllbody->getBody());
	btTransform tf;
	bllbody->getBody()->getMotionState()->getWorldTransform(tf);
	tf.setOrigin(btVector3(0.f, 2.f, 0.f));
	bllbody->getBody()->getMotionState()->setWorldTransform(tf);
	Transform* t1 = new Transform;
	
	poolBall->addComponent(t1);
	entities.addEntity(poolBall);

	SDL_WarpMouseInWindow(Simulator::getInstance().getWindow(), Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

	world->debugDrawWorld();
}