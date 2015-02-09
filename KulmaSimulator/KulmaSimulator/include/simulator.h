#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "game.h"
#include "spritebatch.h"

class Simulator : public Game  {
private:
	Effect* effect;
	GLuint vbo = 0;
	GLuint vao = 0;
	Texture* texture;
	Texture* texture2;
	GLuint IBO = 0;
	SpriteBatch spriteBatch;
public:
	Simulator();
	~Simulator();
	void update(float tpf);
	void draw();
	void initialize();
};


#endif