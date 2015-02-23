#include "engine/camera.h"

Camera::Camera(float fov, float ar, float near, float far) :
	projection(glm::perspective(fov, ar, near, far)),
	view(glm::lookAt(
		glm::vec3(1.0, 2.0, 10.0),   // eye
		glm::vec3(0.0, 0.0, 0.0),   // direction
		glm::vec3(0.0, 1.0, 0.0)  // up
	)) { }


Camera::~Camera() {}
const glm::mat4 Camera::getCamera() const {
	return projection * view;
}