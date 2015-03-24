#ifndef RIGIDBODY3D_H
#define RIGIDBODY3D_H

#include "bullet/btBulletDynamicsCommon.h"
#include "Component.h"

class Rigidbody3D : public Component {
private:
	btRigidBody* body;
	btCollisionShape* shape;
public:
	Rigidbody3D() { }
	~Rigidbody3D() = default;
	btRigidBody* getBody();
protected:
	void onInitialize();
	void onUpdate(float tpf);
};

#endif