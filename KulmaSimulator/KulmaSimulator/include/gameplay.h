#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "engine/gamestates.h"
class Texture;
#include "EntityManager.h"
#include "World.h"
class GameplayState : public GameState {
private:
	World world;
	Texture* texture;
	EntityManager entityManager;
public:
	GameplayState();
	~GameplayState();
	void update(float tpf);
	void draw(SpriteBatch& spriteBatch);
protected:
	void onInitialize();
};

#endif