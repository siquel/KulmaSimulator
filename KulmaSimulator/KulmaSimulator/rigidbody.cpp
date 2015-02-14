#include "rigidbody.h"

Rigidbody::Rigidbody(World& world) : Component(0), world(world.getBox2D()) {
	enable();
}

Rigidbody::~Rigidbody() {}

void Rigidbody::onInitialize() {

}