#pragma once
#include "Component.h"
#include "spritebatch.h"
// Base class for components that can draw.
class DrawableComponent : public Component
{
private:
	int drawOrder;

	bool visible;
protected:
	virtual void onDraw(SpriteBatch& spriteBatch);

	virtual void onVisibleChanged(const bool newVisibility, const bool oldVisibility);

	virtual void drawOrderChanged(const int newOrder, const int oldOrder);
public:
	int getDrawOrder() const;

	DrawableComponent(const int updateOrder = 0, const int drawOrder = 0);

	void show();
	void hide();
	bool isVisible() const;

	void draw(SpriteBatch& spriteBatch);

	virtual ~DrawableComponent();
};

