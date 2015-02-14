#include "Entity.h"

int Entity::idCounter = 0;

Entity::Entity() : id(idCounter++), visible(true), enabled(true), destroyed(false), components(this) {
}

#pragma region Public members
int Entity::getID() const {
	return id;
}
float Entity::getWidth() const {
	return size.x;
}
float Entity::getHeight() const {
	return size.y;
}
void Entity::setWidth(float value) {
	size.x = value;
}
void Entity::setHeight(float value) {
	size.y = value;
}

glm::vec2& Entity::getSize() {
	return size;
}
void Entity::setSize(const glm::vec2& value) {
	size = value;
}

glm::vec2& Entity::getPosition() {
	return position;
}
void Entity::setPosition(const glm::vec2& value)  {
	position = value;
}

void Entity::show() {
	visible = true;
}
void Entity::hide() {
	visible = false;
}
bool Entity::isVisible() const {
	return visible;
}

void Entity::enable() {
	enabled = true;
}
void Entity::disable() {
	enabled = false;
}
bool Entity::isEnabled() const {
	return enabled;
}

void Entity::destroy() {
	if (destroyed) {
		return;
	}

	components.freeComponents();

	for_each(childs.begin(), childs.end(), [](Entity* c) {
		c->destroy();
	});

	childs.clear();

	destroyed = true;
}
bool Entity::isDestroyed() const {
	return destroyed;
}

// All wrapper methods return false if the entity is in destroyed state and 
// wont complete the wanted operation (adding/removing tags).

// Component manager wrappers.
bool Entity::addComponent(Component* component) {
	if (destroyed) return false;

	assert(component != nullptr);

	return components.addComponent(component);
}
bool Entity::removeComponent(Component* component) {
	if (destroyed) return false;

	assert(component != nullptr);
	
	return components.removeComponent(component);
}
bool Entity::containsComponent(const Component* const component) const {
	if (destroyed) return false;

	assert(component != nullptr);

	return components.containsComponent(component);
}

// Tag container wrappers.
bool Entity::unTag(const std::string& tag) {
	if (destroyed) return false;

	return tags.unTag(tag);
}
bool Entity::isTagged(const std::string& tag) const {
	if (destroyed) return false;

	return tags.isTagged(tag);
}
bool Entity::tag(const std::string& tag) {
	if (destroyed) return false;

	return tags.tag(tag);
}

bool Entity::isParentOf(const Entity* const child) {
	assert(child != nullptr);
	
	return std::find(childs.begin(), childs.end(), child) != childs.end();
}
bool Entity::addChild(Entity* const child) {
	if (destroyed) return false;

	bool add = !isParentOf(child);

	if (add) {
		childs.push_back(child);
	}

	return add;
}
bool Entity::removeChild(Entity* const child) {
	if (destroyed) return false;

	bool remove = isParentOf(child);

	if (remove) {
		childs.remove(child);
	}

	return remove;
}

// Update all components that are enabled if entity is in enabled
// state, and is not destroyed.
void Entity::update(float tpf) {
	if (!enabled || destroyed) {
		return;
	}

	components.update(tpf);
}

// Draw all components that are visible if entity is in enabled
// state, and is not destroyed.
void Entity::draw(SpriteBatch& spriteBatch) {
	if (!visible || destroyed) {
		return;
	}

	components.draw(spriteBatch);
}
#pragma endregion

Entity::~Entity() {
}
