#include "Component.h"

Component::Component(const int updateOrder) 
	: owner(nullptr), updateOrder(updateOrder), destroyed(false), enabled(false), initialized(false) {
}

#pragma region Protected members
Entity* Component::getOwner() const {
	return owner;
}

void Component::onUpdate(float tpf) { }

void Component::onDestroyed() { }

void Component::onEnabledChanged(const bool oldState, const bool newState) { }

void Component::onInitialize() { }

void Component::updateOrderChanged(const int newOrder, const int oldOrder) { }
#pragma endregion

#pragma region Public members

void Component::setOwner(Entity* e) {
	owner = e;
}


int Component::getUpdateOrder() const {
	return updateOrder;
}
void Component::changeUpdateOrder(const int newOrder) {
	if (newOrder != updateOrder) {
		int oldOrder = updateOrder;

		updateOrder = newOrder;

		updateOrderChanged(oldOrder, newOrder);
	}
}

void Component::enable() {
	// Do initialization if this is the first
	// call to enable.
	if (!enabled && !initialized) {
		onInitialize();

		initialized = true;
		enabled = true;

		return;
	}

	if (enabled) {
		return;
	}

	enabled = true;

	onEnabledChanged(true, false);
}
void Component::disable() {
	if (!enabled) {
		return;
	}

	enabled = false;

	onEnabledChanged(false, true);
}
bool Component::isEnabled() const {
	return enabled;
}

void Component::destroy() {
	if (destroyed) {
		return;
	}

	destroyed = true;
	
	onDestroyed();
}
bool Component::isDestroyed() const {
	return destroyed;
}

void Component::update(float tpf) {
	if (!enabled || destroyed) {
		return;
	}

	onUpdate(tpf);
}
#pragma endregion

Component::~Component() {
}

