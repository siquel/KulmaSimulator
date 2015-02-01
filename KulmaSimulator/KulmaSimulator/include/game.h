#ifndef GAME_H
#define GAME_H
#include <GL/glew.h>
#include <SDL\SDL.h>
#include "input.h"
#include "content.h"
#include "gamestates.h"
class Game {
protected:
	InputManager input;
	ContentManager content;
	GameStateManager stateManager;

	SDL_Window* window;
	SDL_GLContext context;
	bool running;
	// init SDL and OpenGL
	void init();
public:
	Game();
	~Game();
	virtual void initialize() = 0;
	// called every frame
	virtual void update() = 0;
	// draw stuff
	virtual void draw() = 0;
	// runs the game loop
	void run();

	InputManager& getInput();

	static const int WINDOW_WIDTH = 1280;
	static const int WINDOW_HEIGHT = 720;
};


#endif