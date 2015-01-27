#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

class GameStateManager {
public:
	GameStateManager();
	~GameStateManager();
	// push to front
	void push();
	// pop from front
	void pop();
	// pop front and push to front
	void change();
};

#endif