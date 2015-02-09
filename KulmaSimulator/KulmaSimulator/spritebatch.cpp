#include "spritebatch.h"
#include <algorithm>
#include "util.h"

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

void SpriteBatch::draw(const glm::vec2& pos, Texture* texture) {
	
	if (spriteQueueCount >= spriteQueueArraySize) {
		growSpriteQueue();
	}

	SpriteInfo* sprite = &spriteQueue[spriteQueueCount];

	// we dont have source rect yet
	static const glm::vec4 source = { 0.f, 0.f, 1.f, 1.f };
	// neither colors
	static const glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };
	sprite->source = source;
	sprite->color = color;
	sprite->topLeft = pos;
	sprite->topRight = glm::vec2((pos.x + texture->width) , (pos.y));
	sprite->bottomLeft = glm::vec2(pos.x, pos.y + texture->height);
	sprite->bottomRight = glm::vec2((pos.x + texture->width), (pos.y + texture->height));
	
	
	
	sprite->texture = texture;

	spriteQueueCount++;

}

void SpriteBatch::createIndexBuffer() {
	createIndexValues();
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), indices.data(), GL_STATIC_DRAW);
	glAssert();
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
	glAssert();
	// position, color, uv
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, position)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, color)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, uv)));
	glAssert();
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
			return x->texture->getId() < y->texture->getId();
		});
	}

	GLuint stride = sizeof(VertexPositionColorTexture);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glAssert();
	//clear buffer
	glBufferData(GL_ARRAY_BUFFER, spriteQueueCount * VerticesPerSprite * stride, nullptr, GL_DYNAMIC_DRAW);
	glAssert();
	vertices.clear();
}

void SpriteBatch::flushBatch() {

	if (!spriteQueueCount)
		return;

	glActiveTexture(GL_TEXTURE0 + 0);
	
	glAssert();
	effect->bind();

	GLuint matrixLocation = glGetUniformLocation(effect->getProgram(), "enterTheMatrix");
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(enterTheMatrix));

	Texture* batchTexture = nullptr;
	size_t batchStart = 0;
	for (size_t pos = 0; pos < spriteQueueCount; pos++) {
		Texture* texture = sortedSprites[pos]->texture;
		assert(texture != nullptr);

		if (texture != batchTexture) {
			
			if (pos > batchStart) {
				renderBatch(batchTexture, batchStart, pos - batchStart);
			}

			batchTexture = texture;
			batchStart = pos;
		}
	}

	// flush final
	renderBatch(batchTexture, batchStart, spriteQueueCount - batchStart);

	effect->unbind();
	
	// Reset the queue.
	spriteQueueCount = 0;
	vertexBufferPos = 0;
}

void SpriteBatch::renderBatch(Texture* texture, size_t start, size_t count) {

	glBindTexture(GL_TEXTURE_2D, texture->getId());
	glAssert();

	// loop textures
	while (count > 0) {
		size_t batchSize = count;

		std::vector<VertexPositionColorTexture> vertices;
		// generate vertex data
		for (size_t i = start; i < start + batchSize; i++) {
			glm::vec4 c = sortedSprites[i]->color;
			vertices.push_back(VertexPositionColorTexture(sortedSprites[i]->topLeft.x, sortedSprites[i]->topLeft.y, -0.f, c.x, c.y, c.z, c.z, 0.0f, 1.0f));
			vertices.push_back(VertexPositionColorTexture(sortedSprites[i]->topRight.x, sortedSprites[i]->topRight.y, -0.f, c.x, c.y, c.z, c.z,  1.f, 1.f));
			vertices.push_back(VertexPositionColorTexture(sortedSprites[i]->bottomLeft.x, sortedSprites[i]->bottomLeft.y, -0.f, c.x, c.y, c.z, c.z,  0.f, 0.f));
			vertices.push_back(VertexPositionColorTexture(sortedSprites[i]->bottomRight.x, sortedSprites[i]->bottomRight.y, -0.f, c.x, c.y, c.z, c.z, 1.f, 0.f));
		}
		
		glBufferSubData(GL_ARRAY_BUFFER, 
			vertexBufferPos * sizeof(VertexPositionColorTexture) * vertices.size(), 
			sizeof(VertexPositionColorTexture) * vertices.size(), (void*)(vertices.data()));
		glAssert();
		// TODO why this needs to be multiplied by 2?
		glAssert();
		glDrawElements(GL_TRIANGLES, IndicesPerSprite * batchSize, GL_UNSIGNED_SHORT, (void*)((IndicesPerSprite * vertexBufferPos * 2)));
		count -= batchSize;
		// advance
		vertexBufferPos += batchSize;
	}
	glBindTexture(GL_TEXTURE_2D, 0);


}

void SpriteBatch::init() {
	createVertexArray();
	createIndexBuffer();
	effect = content.load<Effect>("shader\\basic");
	enterTheMatrix = glm::ortho(0.f, static_cast<float>(ScreenWidth), static_cast<float>(ScreenHeight), 0.f, -1.f, 1.f);
		
}
