#ifndef GAME_H
#define GAME_H
#include <GL/glew.h>
#include <SDL\SDL.h>
#include "input.h"
#include "content.h"
#include "gamestates.h"
class Game {
private:
	InputManager input;
	ContentManager content;
	GameStateManager stateManager;

	SDL_Window* window;
	SDL_GLContext context;
	bool running;
public:
	Game();
	~Game();
	// init SDL and OpenGL
	void init();
	// called every frame
	virtual void update() = 0;
	// draw stuff
	virtual void draw() = 0;
	// runs the game loop
	void run();

	static const int WINDOW_WIDTH = 1280;
	static const int WINDOW_HEIGHT = 720;
};


#endif