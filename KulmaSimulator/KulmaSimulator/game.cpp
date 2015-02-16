#include "game.h"
#include <cassert>
#include <iostream>
#include "util.h"

Game::Game() : running(false), content("Content") {

}

Game::~Game() {

}

void Game::init() {
	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	window = SDL_CreateWindow("KulmaSimulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	assert(window != nullptr);

	context = SDL_GL_CreateContext(window);
	assert(context != nullptr);
	glewExperimental = GL_TRUE;
	const GLenum glewResult = glewInit();
	assert(glewResult == GLEW_OK);
	glGetError();
	int versionMajor;
	int versionMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MAJOR_VERSION, &versionMinor);
	std::cout << "OpenGL context version: " << versionMajor << '.' << versionMinor << '\n';
	int max;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
	std::cout << "Max texture size: " << max << std::endl;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::run() {
	init();
	initialize();
	running = true;
	SDL_Event event;

	Uint32 oldTime, currentTime;
	oldTime = currentTime = 0;
	float tpf;

	while (running) {
		oldTime = currentTime;
		currentTime = SDL_GetTicks();
		tpf = (currentTime - oldTime) / 1000.0f;
		input.update();
		while (SDL_PollEvent(&event) == 1)
		{
			if (event.type == SDL_QUIT)
				running = false;
		}
		
		update(tpf);
		draw();
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

InputManager& Game::getInput() {
	return input;
}

GameStateManager& Game::getStateManager() {
	return stateManager;
}

ContentManager& Game::getContent() {
	return content;
}