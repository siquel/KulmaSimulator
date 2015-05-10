#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Component.h"
#include "GLM.h"
struct InputArgs;
class PlayerController : public Component {
public:
	PlayerController();
	~PlayerController();
protected:
	void onInitialize();
	void onUpdate(float tpf);

private:
	void moveForward(InputArgs&);
	void moveBackward(InputArgs&);
	void strafeLeft(InputArgs&);
	void strafeRight(InputArgs&);
	void interact(InputArgs&);
	glm::vec3 position;
	glm::vec3 forward;
	float yaw;
	float pitch;
};

#endif