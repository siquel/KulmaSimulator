#ifndef CAMERA_H
#define CAMERA_H
#include "GLM.h"
#include "engine/input.h"
class Camera {
private:
	static const float MovementSpeedFactor;

	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 rotation;
	glm::vec3 position;
	glm::vec3 speed;

	int midWinX;
	int midWinY;

	void moveForward(InputArgs& args);
	void moveBackward(InputArgs& args);

public:
	Camera(float fov, float ar, float near, float far);
	~Camera();
	const glm::mat4 getCamera() const;


	void update(float tpf);
};

#endif