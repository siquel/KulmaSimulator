#ifndef CAMERA_H
#define CAMERA_H
#include "GLM.h"
class Camera {
private:
	glm::mat4 projection;
	glm::mat4 view;
public:
	Camera(float fov, float ar, float near, float far);
	~Camera();
	const glm::mat4 getCamera() const;
};

#endif