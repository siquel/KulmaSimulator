#pragma once

class Entity;
class World;

class EntityBuilder {
public:
	EntityBuilder() = default;
	~EntityBuilder() = default;
	static Entity* buildPoolTable(World& world);
	static Entity* buildPoolBall(World& world);
};