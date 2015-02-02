#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "game.h"
#include "shader.h"

class Simulator : public Game  {
private:
	Shader shader;
	GLuint vbo = 0;
	GLuint vao = 0;
	Texture* texture;
	GLuint IBO = 0;
public:
	Simulator();
	~Simulator();
	void update();
	void draw();
	void initialize();
};


#endif