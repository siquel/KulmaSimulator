#include "spritebatch.h"
#include <algorithm>



SpriteBatch::SpriteBatch() : hasBegun(false), sortMode(SpriteSortMode::Deferred), VAO(0), VBO(0), IBO(0), spriteQueueCount(0), spriteQueueArraySize(0) {

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

void SpriteBatch::draw(const pmath::Vec3f& pos, Texture* texture) {
	
	if (spriteQueueCount >= spriteQueueArraySize) {
		growSpriteQueue();
	}

	SpriteInfo* sprite = &spriteQueue[spriteQueueCount];

	// we dont have source rect yet
	static const pmath::Recti wholeTex = { 0, 0, 1, 1 };
	// neither colors
	static const pmath::Vec4f color = { 1.f, 1.f, 1.f, 1.f };
	sprite->source = wholeTex;
	sprite->pos = pos;
	sprite->texture = texture;

	spriteQueueCount++;

}

void SpriteBatch::createIndexBuffer() {
	createIndexValues();
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
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
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// position, color, uv
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, position)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, color)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, uv)));

	glBindVertexArray(0);
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
	// clear vertex buffer
	GLuint stride = sizeof(VertexPositionColorTexture);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//clear buffer
	glBufferData(GL_ARRAY_BUFFER, spriteQueueCount * VerticesPerSprite * stride, nullptr, GL_DYNAMIC_DRAW);
	
}

void SpriteBatch::flushBatch() {

	if (!spriteQueueCount)
		return;

	Texture* batchTexture = nullptr;
	size_t batchStart = 0;
	for (size_t pos = 0; pos < spriteQueueCount; pos++) {
		// todo convert to sort
		Texture* texture = spriteQueue[pos].texture;
		assert(texture != nullptr);

		if (texture != batchTexture) {
			if (pos > batchStart) {
				// todo convert to sorted
				renderBatch(batchTexture, &spriteQueue[pos], pos - batchStart);
			}
		}
	}

	// flush final, todo convert to sorted
	renderBatch(batchTexture, &spriteQueue[batchStart], spriteQueueCount - batchStart);

	// Reset the queue.
	spriteQueueCount = 0;
}

void SpriteBatch::renderBatch(Texture* texture, SpriteInfo* sprites, size_t count) {
	// loop textures
	while (count > 0) {
		size_t batchSize = count;
		// generate vertex data

		static const float transformation[] = {
			1.0, 0.f,
			0.0, 1.0f,
			1.0f, 0.0f,
			0.0, 0.0f
		};

		// send to gpu
		// instantiate buffer again, from loc?
		//glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * stride, vertices.data());
		// advance
		sprites += batchSize;
		count -= batchSize;
	}


}

void SpriteBatch::init() {
	createVertexArray();
	createIndexBuffer();
}
