#include "EntityManager.h"

EntityManager::EntityManager() {
}

#pragma region Private members
void EntityManager::freeEntities() {
	std::for_each(destroyedEntities.begin(), destroyedEntities.end(), [this](Entity* e) {
		entities.remove(e);

		delete e;
		e = nullptr;
	});

	destroyedEntities.clear();
}
#pragma endregion

#pragma region Public memebers
bool EntityManager::addEntity(Entity* const entity) {
	assert(entity != nullptr && !entity->isDestroyed());
	
	bool add = !containsEntity(entity);

	if (add) {
		entities.push_back(entity);
	}

	return add;
}
bool EntityManager::removeEntity(Entity* const entity) {
	assert(entity != nullptr);

	bool remove = containsEntity(entity);

	if (remove) {
		entities.remove(entity);
	}

	return remove;
}

bool EntityManager::containsEntity(const Entity* const entity) const {
	return std::find(entities.begin(), entities.end(), entity) != entities.end();
}

std::vector<Entity* const>& EntityManager::findEntitiesWithTag(const std::string& tag) {
	findResults.clear();

	std::for_each(entities.begin(), entities.end(), [this, &tag](Entity* e) {
		if (e->isTagged(tag)) {
			findResults.push_back(e);
		}
	});

	return findResults;
}

Entity* const EntityManager::findEntityWithTag(const std::string& tag) const {
	auto result = std::find_if(entities.begin(), entities.end(), [this, &tag](Entity* e) {
		return e->isTagged(tag);
	});

	return *result;
}
Entity* const EntityManager::findEntityWithID(const int id) const {
	auto result = std::find_if(entities.begin(), entities.end(), [this, &id](Entity* e) {
		return e->getID() == id;
	});

	return *result;
}

void EntityManager::update() {
	freeEntities();
	
	std::for_each(entities.begin(), entities.end(), [this](Entity* e) {
		if (e->isDestroyed()) {
			destroyedEntities.push_back(e);

			return;
		}

		e->update();
	});
}
void EntityManager::draw() {
	std::for_each(entities.begin(), entities.end(), [](Entity* e) {
		e->draw();
	});
}
#pragma endregion

EntityManager::~EntityManager() {
	std::_For_each(entities.begin(), entities.end(), [](Entity* e) {
		// No need to call destroy here.
		delete e;
		e = nullptr;
	});
}