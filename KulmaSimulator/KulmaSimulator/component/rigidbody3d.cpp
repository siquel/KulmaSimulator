#include "component/rigidbody3d.h"
#include "Entity.h"
#include "component/transform.h"
#include <iostream>
void Rigidbody3D::onInitialize() {
	shape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
	btDefaultMotionState* motionState = new btDefaultMotionState();
	btRigidBody::btRigidBodyConstructionInfo ci(
		0.f,
		motionState,
		shape,
		btVector3(0, 0, 0)
		);
	body = new btRigidBody(ci);
}

void Rigidbody3D::onUpdate(float tpf) {
	Transform* tf = getOwner()->getComponent<Transform>();
	btTransform transf;
	body->getMotionState()->getWorldTransform(transf);
	tf->setPosition(
		glm::vec3(
		transf.getOrigin().getX(),
		transf.getOrigin().getY(),
		transf.getOrigin().getZ()));
}

btRigidBody* Rigidbody3D::getBody() {
	return body;
}