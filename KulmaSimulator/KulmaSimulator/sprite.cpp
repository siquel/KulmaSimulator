#include "sprite.h"


Sprite::Sprite(const Texture* texture,
	const glm::vec2& position = glm::vec2(0.f, 0.f),
	const glm::vec4& color = glm::vec4(1.f, 1.f, 1.f, 1.f),
	const glm::vec2& scale = glm::vec2(1.f, 1.f),
	const glm::vec2& origin = glm::vec2(0.f, 0.f), float rotation = 0.f)
	: texture(texture), position(position), color(color), scale(scale), origin(origin), rotation(rotation), source(0.f, 0.f, 0.f, 0.f) {
	assert(texture != nullptr);
	source.z = static_cast<float>(texture->width);
	source.w = static_cast<float>(texture->height);
}

Sprite::~Sprite() {

}

void Sprite::draw(SpriteBatch& spriteBatch) {
	spriteBatch.draw(texture, position, &source, color, scale, origin, rotation);
}


SpriteRenderer::SpriteRenderer(Entity& owner, Sprite& sprite, const int updateOrder, const int drawOrder)
	: DrawableComponent(owner, updateOrder, drawOrder), sprite(sprite) {
}


void SpriteRenderer::onDraw(SpriteBatch& spriteBatch) {
	sprite.draw(spriteBatch);
}