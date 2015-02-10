#include "ComponentManager.h"

ComponentManager::ComponentManager() {
}

#pragma region Private members
void ComponentManager::freeDestroyedComponents() {
	if (destroyedComponents.size() > 0) {
		std::for_each(destroyedComponents.begin(), destroyedComponents.end(), [this](Component* component) {
			components.remove(component);

			// Check if the component is drawable one.
			DrawableComponent* drawableComponent = dynamic_cast<DrawableComponent*>(component);

			if (drawableComponent != nullptr) {
				drawableComponents.remove(drawableComponent);
			}

			// Just release the memory, destroy has already been called.
			delete component;
			component = nullptr;
		});

		destroyedComponents.clear();
	}
}
#pragma endregion

#pragma region Public members
bool ComponentManager::containsComponent(const Component* const component) const {
	return std::find(components.begin(), components.end(), component) != components.end();
}
bool ComponentManager::removeComponent(Component* const component) {
	assert(component != nullptr);
	
	bool remove = containsComponent(component);

	if (remove) {
		components.remove(component);
		
		DrawableComponent* drawableComponent = dynamic_cast<DrawableComponent*>(component);

		if (drawableComponent != nullptr) {
			drawableComponents.remove(drawableComponent);
		}
	}

	return remove;
}
bool ComponentManager::addComponent(Component* const component) {
	assert(component != nullptr && !component->isDestroyed());
	
	bool add = !containsComponent(component);

	if (add) {
		// TODO: could just check beg and end to skip sorting?
		// TODO: sorting is performed only when component is added.
		
		// Check if component is drawable.
		DrawableComponent* drawableComponent = dynamic_cast<DrawableComponent*>(component);

		if (drawableComponent != nullptr) {
			drawableComponents.push_back(drawableComponent);

			drawableComponents.sort([](DrawableComponent* a, DrawableComponent* b) {
				return a->getDrawOrder() < b->getDrawOrder();
			});
		}

		components.push_back(component);

		components.sort([](Component* a, Component* b) {
			return a->getUpdateOrder() < b->getUpdateOrder();
		});
	}

	return add;
}

void ComponentManager::freeComponents() {
	std::for_each(components.begin(), components.end(), [](Component* c) {
		if (c->isDestroyed()) {
			return;
		}

		c->destroy();

		delete c;
		c = 0;
	});

	components.clear();
	drawableComponents.clear();
	destroyedComponents.clear();
}

void ComponentManager::update() {
	freeDestroyedComponents();
	
	std::for_each(components.begin(), components.end(), [this](Component* c) {
		// Component was destroyed in last frame, some other
		// component destroyed it or it was destroyed during 
		// draw call.
		if (c->isDestroyed()) {
			destroyedComponents.push_back(c);

			return;
		}

		c->update();
	});
}
void ComponentManager::draw() {
	std::for_each(drawableComponents.begin(), drawableComponents.end(), [this](DrawableComponent* c) {
		c->draw();
	});
}
#pragma endregion 

// Call destroy for all components and release them.
ComponentManager::~ComponentManager() {
	freeComponents();
}
