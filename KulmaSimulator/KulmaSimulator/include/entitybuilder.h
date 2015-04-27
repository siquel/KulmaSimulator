#pragma once
#include "GLM.h"
class Entity;
class World;
class EntityManager;
class EntityBuilder {
public:
	EntityBuilder() = default;
	~EntityBuilder() = default;
	static Entity* buildPoolTable(World& world);
	static Entity* buildPoolBall(World& world, float x, float y);
	static Entity** buildPooBallTriangle(World& world);
	static Entity* buildKulma(EntityManager&);
private:
	static Entity* createWall(const glm::vec3& pos, const glm::vec3& scale);
	static Entity* createTableGroup(const glm::vec3& pos, float rotation, const glm::vec3& axis);
};