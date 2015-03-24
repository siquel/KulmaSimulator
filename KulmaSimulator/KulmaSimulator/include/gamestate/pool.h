#ifndef POOL_H
#define POOL_H
#include "engine/gamestates.h"
#include "EntityManager.h"


#include "bullet/btBulletDynamicsCommon.h"

class PoolState : public GameState {

private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* world;
public:
	void update(float tpf);
	void draw(SpriteBatch& spriteBatch);
	PoolState();
	~PoolState();
protected:
	void onInitialize();
private:
	EntityManager entities;
};


#endif