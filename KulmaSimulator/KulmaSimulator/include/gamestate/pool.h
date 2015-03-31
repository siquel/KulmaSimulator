#ifndef POOL_H
#define POOL_H
#include "engine/gamestates.h"
#include "EntityManager.h"
#include "world.h"
#include "box2Ddebugdraw.h"
class PoolState : public GameState {
public:
	void update(float tpf);
	void draw(SpriteBatch& spriteBatch);
	PoolState();
	~PoolState();
protected:
	void onInitialize();
private:
	Box2DDebugDraw debugdraw;
	EntityManager entities;
	World world;
};


#endif