#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "engine/gamestates.h"
class Texture;
#include "collision_listener.h"
#include "EntityManager.h"
#include "World.h"
class GameplayState : public GameState {
private:
	World world;
	Texture* texture;
	EntityManager entityManager;
	ContactListener collisionListener;
public:
	GameplayState();
	~GameplayState();
	void update(float tpf);
	void draw(SpriteBatch& spriteBatch);
protected:
	void onInitialize();
	void onUnload() override;
};

#endif