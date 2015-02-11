#ifndef SPRITE_H
#define SPRITE_H
#include "resources.h"
#include "spritebatch.h"
#include "GLM.h"

#include "DrawableComponent.h"

class Sprite {
public:
	const Texture* texture;
	glm::vec2 position;
	glm::vec2 origin;
	glm::vec2 scale;
	glm::vec4 color;
	glm::vec4 source;
	float rotation;
	
	Sprite(const Texture* texture, const glm::vec2& position, const glm::vec4& color, const glm::vec2& scale, const glm::vec2& origin, float rotation);
	~Sprite();
	void draw(SpriteBatch& spriteBatch);
};

class SpriteRenderer : public DrawableComponent {
private:
	Sprite sprite;
public:
	SpriteRenderer(Entity& owner, Sprite& sprite, const int updateOrder, const int drawOrder);
	void onDraw(SpriteBatch& spriteBatch);
};

#endif