#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include "GL\glew.h"
#include "pmath\Vector.hpp"
#include "content.h"

struct SpriteInfo {
	pmath::Vec3f pos;
	pmath::Vec4f color;
	pmath::Vec2f uv;
	Texture* texture;
};

class SpriteBatch {
private:
	GLuint VBO = 0;
	GLuint IBO = 0;
	GLuint VAO = 0;
	bool hasBegun;
	std::vector<SpriteInfo> spriteQueue;

	void createVertexArray();
	void createIndexBuffer();
	std::vector<unsigned short> indices;

	const int IndicesPerSprite = 6;
	const int VerticesPerSprite = 4;

public:
	SpriteBatch();
	~SpriteBatch();

	void begin();
	void end();
	void draw(const pmath::Vec4f& rekt);
};

#endif