#include "rigidbody.h"

Rigidbody::Rigidbody(World& world) : Component(0), world(world.getBox2D()) {

}

Rigidbody::~Rigidbody() {}

void Rigidbody::onInitialize() {

}