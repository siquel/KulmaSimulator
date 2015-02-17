#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include "spritebatch.h"

class GameState {
private:
	bool initialized;
public:
	GameState();
	virtual ~GameState();
	virtual void update(float tpf) = 0;
	virtual void draw(SpriteBatch& spriteBatch) = 0;
	void init();
protected:
	virtual void onInitialize() = 0;
};

class GameStateManager {
private:
	std::vector<GameState*> states;
public:
	GameStateManager();
	~GameStateManager();
	// push to front
	void push(GameState*);
	// pop from front
	void pop();
	// pop front and push to front
	void change(GameState*);

	void update(float tpf);
	void draw(SpriteBatch& spriteBatch);
};



#endif