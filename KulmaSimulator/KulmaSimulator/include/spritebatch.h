#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include "GL\glew.h"
#include "GLM.h"
#include "engine/content.h"
#include <memory>
#include "util.h"
class Effect;

enum SpriteSortMode {
	Deferred
};

__declspec(align(16)) struct SpriteInfo : public AlignedNew<SpriteInfo> {
	glm::vec2 topLeft;
	glm::vec2 topRight;
	glm::vec2 bottomLeft;
	glm::vec2 bottomRight;
	glm::vec4 color;
	glm::vec4 texCoords;
	const Texture* texture;
};

struct VertexPositionColorTexture {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uv;

	VertexPositionColorTexture(float x, float y, float z, float r, float g, float b, float a, float u, float v) 
		: position(x, y, z), color(r, g, b, a), uv(u, v)
	{}
};

class SpriteBatch {
private:
	unsigned int vertexBufferPos;
	std::vector<VertexPositionColorTexture> vertices;
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
	static const size_t MaxBatchSize = 2048;

	// when we sort sprites, they'll be stored here
	std::vector<SpriteInfo const*> sortedSprites;

	// helpers
	void growSpriteQueue();
	// sends sprites to GPU + calculates vertices
	void renderBatch(const Texture* texture, size_t start, size_t count);
	glm::mat4 enterTheMatrix;

	//prevent copying
	SpriteBatch(SpriteBatch const&);
	SpriteBatch& operator=(SpriteBatch const&);
public:
	SpriteBatch();
	~SpriteBatch();

	// temporary, gotta move context creation to somewhere else
	void init();

	void begin(SpriteSortMode spriteSortMode);
	void end();
	void draw(const Texture* texture, const glm::vec2& pos);
	void draw(const Texture* texture, const glm::vec2& pos, const glm::vec4& color);
	void draw(const Texture* texture, const glm::vec2& pos, const glm::vec4* source, const glm::vec4& color);
	void draw(const Texture* texture, const glm::vec2& pos, const glm::vec4& color, const glm::vec2& scale);
	void draw(const Texture* texture, const glm::vec2& pos, const glm::vec4* source, const glm::vec4& color, const glm::vec2& scale);
	void draw(const Texture* texture, const glm::vec2& pos, const glm::vec4& color, const glm::vec2& scale, const glm::vec2& origin, float rotation);
	void draw(const Texture* texture, const glm::vec2& pos, const glm::vec4* source, const glm::vec4& color, const glm::vec2& scale, const glm::vec2& origin, float rotation);
	
};

#endif