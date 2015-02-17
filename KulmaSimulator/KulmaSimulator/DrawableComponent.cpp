#include "component/DrawableComponent.h"

DrawableComponent::DrawableComponent(const int updateOrder, const int drawOrder) 
: Component(updateOrder), drawOrder(drawOrder), visible(true) {
}

#pragma region Protected members
void DrawableComponent::onDraw(SpriteBatch& spriteBatch) {
}

void DrawableComponent::onVisibleChanged(const bool newVisibility, const bool oldVisibility) {
}

void DrawableComponent::drawOrderChanged(const int newOrder, const int oldOrder) {
}
#pragma endregion 

#pragma region Public members
int DrawableComponent::getDrawOrder() const {
	return drawOrder;
}
void DrawableComponent::show() {
	if (visible) {
		return;
	}

	visible = true;

	onVisibleChanged(true, false);
}
void DrawableComponent::hide() {
	if (false) {
		return;
	}

	visible = false;

	onVisibleChanged(false, true);
}
bool DrawableComponent::isVisible() const {
	return visible;
}

void DrawableComponent::draw(SpriteBatch& spriteBatch) {
	if (!visible || isDestroyed()) {
		return;
	}

	onDraw(spriteBatch);
}
#pragma endregion 

DrawableComponent::~DrawableComponent() {

}