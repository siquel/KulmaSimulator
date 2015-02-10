#pragma once
#include "DrawableComponent.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <list>

class ComponentManager {
private:
	std::list<Component* const> components;
	std::list<DrawableComponent* const> drawableComponents;

	std::list<Component* const> destroyedComponents;

	void freeDestroyedComponents();
public:
	ComponentManager();

	bool containsComponent(const Component* const component) const;
	bool removeComponent(Component* const component);
	bool addComponent(Component* const component);

	void freeComponents();

	void update();
	void draw();

	template<class T> T* const getComponent() const {
		T* foundComponent = nullptr;

		std::find_if(components.begin(), components.end(), [=, &foundComponent](Component* component) {
			foundComponent = dynamic_cast<T*>(component);

			return foundComponent != nullptr;
		});

		return foundComponent;
	}

	Component* const getComponent(std::function<bool(Component const*)> predicate) {
		auto result = std::find_if(components.begin(), components.end(), predicate);

		return *result;
	}

	~ComponentManager();
};

