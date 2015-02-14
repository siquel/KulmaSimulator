#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "gamestates.h"
#include "resources.h"
#include "EntityManager.h"

class GameplayState : public GameState {
private:
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