#ifndef SPRITE_H
#define SPRITE_H
#include "spritebatch.h"
#include "GLM.h"
#include "component/DrawableComponent.h"

class Sprite : public AlignedNew<Sprite> {
public:
	const Texture* texture;
	glm::vec2 position;
	glm::vec2 origin;
	glm::vec2 scale;
	glm::vec4 color;
	glm::vec4 source;
	float rotation;
	
	__declspec(align(16)) Sprite(const Texture* texture, const glm::vec2& position, const glm::vec4& color, const glm::vec2& scale, const glm::vec2& origin, float rotation);
	~Sprite();
	void draw(SpriteBatch& spriteBatch);
};

class SpriteRenderer : public DrawableComponent, public AlignedNew<SpriteRenderer> {
private:
	Sprite sprite;
public:
	__declspec(align(16)) SpriteRenderer(Sprite& sprite, const int updateOrder, const int drawOrder);
	void onDraw(SpriteBatch& spriteBatch);
};

#endif