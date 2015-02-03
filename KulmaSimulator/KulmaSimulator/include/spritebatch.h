#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include "GL\glew.h"
#include "pmath\Vector.hpp"
#include <pmath\Rectangle.hpp>
#include "content.h"
#include <memory>

enum SpriteSortMode {
	Deferred
};

struct SpriteInfo {
	pmath::Vec3f pos;
	pmath::Vec4f color;
	pmath::Vec2f uv;
	pmath::Recti source;
	Texture* texture;
};

struct VertexPositionColorTexture {
	pmath::Vec3f position;
	pmath::Vec4f color;
	pmath::Vec2f uv;

	VertexPositionColorTexture(float x, float y, float z, float r, float g, float b, float a, float u, float v) 
		: position(x, y, z), color(r, g, b, a), uv(u, v)
	{}
};

class SpriteBatch {
private:
	ContentManager content;
	Effect* effect;
	SpriteSortMode sortMode;

	GLuint VBO = 0;
	GLuint IBO = 0;
	GLuint VAO = 0;
	bool hasBegun;
	// sprites to be drawn
	std::unique_ptr<SpriteInfo[]> spriteQueue;
	// how many sprites there are to be drawn
	size_t spriteQueueCount;
	// size of spriteQueue
	size_t spriteQueueArraySize;

	void createVertexArray();
	void createIndexBuffer();
	void createIndexValues();

	void prepareForRendering();
	void flushBatch();

	std::vector<unsigned short> indices;

	static const size_t IndicesPerSprite = 6;
	static const size_t VerticesPerSprite = 4;
	static const size_t InitialQueueSize = 64;
	static const size_t MaxBatchSize = 256;

	// when we sort sprites, they'll be stored here // not implemented
	std::vector<SpriteInfo const*> sortedSprites;

	// helpers
	void growSpriteQueue();
	// sends sprites to GPU
	void renderBatch(Texture* texture, SpriteInfo* sprites, size_t count);
public:
	SpriteBatch();
	~SpriteBatch();

	// temporary, gotta move context creation to somewhere else
	void init();

	void begin(SpriteSortMode spriteSortMode);
	void end();
	void draw(const pmath::Vec3f& pos, Texture* texture);
	// debug
	void draw(const pmath::Vec4f& rect);
};

#endif