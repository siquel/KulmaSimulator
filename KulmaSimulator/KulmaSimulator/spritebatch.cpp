#include "spritebatch.h"
#include <algorithm>
// todo hax
#define ScreenWidth 1280
#define ScreenHeight 720

SpriteBatch::SpriteBatch() : hasBegun(false), sortMode(SpriteSortMode::Deferred), VAO(0), VBO(0), IBO(0), spriteQueueCount(0), spriteQueueArraySize(0), content("Content"), effect(nullptr), vertexBufferPos(0) {

}

SpriteBatch::~SpriteBatch() {

}

void SpriteBatch::begin(SpriteSortMode spriteSortMode) {
	if (hasBegun) {
		throw std::logic_error("End must be called");
	}
	sortMode = spriteSortMode;
	hasBegun = true;
}

void SpriteBatch::end() {
	
	hasBegun = false;

	prepareForRendering();
	flushBatch();
}

void SpriteBatch::draw(const pmath::Vec2f& pos, Texture* texture) {
	
	if (spriteQueueCount >= spriteQueueArraySize) {
		growSpriteQueue();
	}

	SpriteInfo* sprite = &spriteQueue[spriteQueueCount];

	// we dont have source rect yet
	static const pmath::Vec4f source = { 0.f, 0.f, 1.f, 1.f };
	// neither colors
	static const pmath::Vec4f color = { 1.f, 1.f, 1.f, 1.f };
	sprite->source = source;
	sprite->color = color;
	sprite->topLeft = pmath::Vec2f(pos.x / ScreenWidth, pos.y / ScreenHeight);
	sprite->topRight = pmath::Vec2f((pos.x + texture->width)/ScreenWidth, (pos.y) / ScreenHeight);
	sprite->bottomRight = pmath::Vec2f((pos.x + texture->width) / ScreenWidth, (pos.y + texture->height) / ScreenHeight);
	sprite->bottomLeft = pmath::Vec2f((pos.x) / ScreenWidth, (pos.y + texture->height) / ScreenHeight);
	
	sprite->texture = texture;

	spriteQueueCount++;

}

void SpriteBatch::createIndexBuffer() {
	createIndexValues();
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

void SpriteBatch::createIndexValues() {
	indices.reserve(IndicesPerSprite * MaxBatchSize);
	// these won't change
	for (unsigned short i = 0; i < MaxBatchSize * IndicesPerSprite; i += VerticesPerSprite)
	{
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 2);

		indices.push_back(i + 1);
		indices.push_back(i + 3);
		indices.push_back(i + 2);
	}
}


void SpriteBatch::createVertexArray() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//createIndexBuffer();
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// position, color, uv
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, position)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, color)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, uv)));
	vertices.reserve(InitialQueueSize * VerticesPerSprite);
}

void SpriteBatch::growSpriteQueue() {
	// grow by factor 2
	size_t newSize = std::max(InitialQueueSize, spriteQueueArraySize * 2);
	// alloc
	std::unique_ptr<SpriteInfo[]> array(new SpriteInfo[newSize]);
	// copy
	for (size_t i = 0; i < spriteQueueCount; i++) {
		array[i] = spriteQueue[i];
	}
	// replace prev array w/ new one
	spriteQueue = std::move(array);
	spriteQueueArraySize = newSize;

	sortedSprites.clear();
}

void SpriteBatch::prepareForRendering() {

	// sort sprites && grow if necessary
	if (sortedSprites.size() < spriteQueueCount) {
		size_t prev = sortedSprites.size();
		sortedSprites.resize(spriteQueueCount);
		for (size_t i = prev; i < spriteQueueCount; i++) {
			sortedSprites[i] = &spriteQueue[i];
		}

		std::sort(sortedSprites.begin(), sortedSprites.begin() + spriteQueueCount, [](const SpriteInfo* x, const SpriteInfo* y) {
			return x->texture < y->texture;
		});
	}

	GLuint stride = sizeof(VertexPositionColorTexture);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//clear buffer
	glBufferData(GL_ARRAY_BUFFER, spriteQueueCount * VerticesPerSprite * stride, nullptr, GL_DYNAMIC_DRAW);
	vertices.clear();
}

void SpriteBatch::flushBatch() {

	if (!spriteQueueCount)
		return;

	Texture* batchTexture = nullptr;
	size_t batchStart = 0;
	for (size_t pos = 0; pos < spriteQueueCount; pos++) {
		Texture* texture = sortedSprites[pos]->texture;
		assert(texture != nullptr);

		if (texture != batchTexture) {
			
			if (pos > batchStart) {
				renderBatch(batchTexture, &sortedSprites[pos], pos - batchStart);
			}

			batchTexture = texture;
			batchStart = pos;
		}
	}

	// flush final
	renderBatch(batchTexture, &sortedSprites[batchStart], spriteQueueCount - batchStart);

	// Reset the queue.
	spriteQueueCount = 0;
	vertexBufferPos = 0;
}

void SpriteBatch::renderBatch(Texture* texture, SpriteInfo const* const* sprites, size_t count) {
	
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture->getId());
	effect->bind();

	// loop textures
	while (count > 0) {
		size_t batchSize = count;

		GLuint scaleLocation = glGetUniformLocation(effect->getProgram(), "scale");
		glUniform3f(scaleLocation, 1.f, 1.f, 1.f);
		
		// generate vertex data
		for (size_t i = 0; i < batchSize; i++) {

			vertices.push_back(VertexPositionColorTexture(sprites[i]->topLeft.x, sprites[i]->topLeft.y, 0.f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f));
			vertices.push_back(VertexPositionColorTexture(sprites[i]->topRight.x, sprites[i]->topRight.y, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.f, 1.f));
			vertices.push_back(VertexPositionColorTexture(sprites[i]->bottomLeft.x, sprites[i]->bottomLeft.y, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.f));
			vertices.push_back(VertexPositionColorTexture(sprites[i]->bottomRight.x, sprites[i]->bottomRight.y, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.f, 0.f));
		}

		glBufferSubData(GL_ARRAY_BUFFER, vertexBufferPos * sizeof(VertexPositionColorTexture) * VerticesPerSprite, sizeof(VertexPositionColorTexture) * VerticesPerSprite * batchSize, (void*)(vertices.data() + vertexBufferPos * VerticesPerSprite));
		glDrawElements(GL_TRIANGLES, IndicesPerSprite * batchSize, GL_UNSIGNED_SHORT, (void*)(IndicesPerSprite * vertexBufferPos));
		
		sprites += batchSize;
		count -= batchSize;
		// advance
		vertexBufferPos += batchSize;
	}
	
	effect->unbind();

}

void SpriteBatch::init() {
	createVertexArray();
	createIndexBuffer();
	effect = content.load<Effect>("shader\\basic");
}
