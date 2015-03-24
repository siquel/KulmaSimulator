#include "component/rigidbody3d.h"
#include "Entity.h"
#include "component/transform.h"
#include "component/meshrenderer.h"
#include <iostream>
void Rigidbody3D::onInitialize() {
	/*
	Mesh* mesh = getOwner()->getComponent<MeshRenderer>()->getMesh();
	btTriangleMesh* trimesh = new btTriangleMesh;
	const std::vector<float>& vertices = mesh->getVertices();
	for (size_t i = 0; i < mesh->getVertices().size(); i += 8 * 3) {
		btVector3 vertex0(vertices[i], vertices[i + 1], vertices[i + 2]);
		btVector3 vertex1(vertices[i + 8], vertices[i + 8 + 1], vertices[i + 8 + 2]);
		btVector3 vertex2(vertices[i + 16], vertices[i + 16 + 1], vertices[i + 16 + 2]);
		trimesh->addTriangle(vertex0, vertex1, vertex2);
	}

	shape = new btBvhTriangleMeshShape(trimesh, true);*/
	shape = new btBoxShape(btVector3(1.f, 1.f, 1.f));
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