#include "rigidbody.h"

Rigidbody::Rigidbody(Entity* entity, World& world) : Component(*entity), world(world.getBox2D()) {

}

Rigidbody::~Rigidbody() {}

void Rigidbody::onInitialize() {

}