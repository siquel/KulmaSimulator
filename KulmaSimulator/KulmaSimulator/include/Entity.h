#pragma once
#include "TagContainer.h"
#include "ComponentManager.h"
#include "Component.h"
#include "GLM\glm.hpp"

class Entity {
private:
	static int idCounter; 
	
	const int id;
	
	TagContainer tags;
	ComponentManager components;

	bool visible;
	bool enabled;
	bool destroyed;

	glm::vec2 position;
	glm::vec2 size;

	std::list<Entity* const> childs;

	void freeChilds();
public:
	Entity();

	int getID() const;

	float getWidth() const;
	float getHeight() const;
	void setWidth(const float value);
	void setHeight(const float value);

	glm::vec2& getSize();
	void setSize(const glm::vec2& value);
	
	glm::vec2& getPosition();
	void setPosition(const glm::vec2& value);

	void show();
	void hide();
	bool isVisible() const;

	void enable();
	void disable();
	bool isEnabled() const;
	
	void destroy();
	bool isDestroyed() const;

	bool addComponent(Component* const component);
	bool removeComponent(Component* const component);
	bool containsComponent(const Component* const component) const;

	template<class T> T* const getComponent() const {
		return components.getComponent<T>();
	}

	Component* const getComponent(std::function<bool(Component const*)> predicate) {
		return components.getComponent(predicate);
	}

	bool unTag(const std::string& tag);
	bool isTagged(const std::string& tag) const;
	bool tag(const std::string& tag);
	
	bool isParentOf(const Entity* const child);
	bool addChild(Entity* const child);
	bool removeChild(Entity* const child);

	void update();
	void draw(SpriteBatch& spriteBatch);

	~Entity();
};