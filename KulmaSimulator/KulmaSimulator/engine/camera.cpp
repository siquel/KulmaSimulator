#include "engine/camera.h"
#include <gl/glew.h>
#include <SDL/sdl.h>
#include <iostream>

#include "simulator.h"

Camera::Camera(float fov, float ar, float near, float far) :
	projection(glm::perspective(fov, ar, near, far)) {
}

Camera::~Camera() {}
const glm::mat4 Camera::getCamera() const {
	return projection * view;
}

void Camera::setView(glm::mat4& view) {
	this->view = view;
}

void Camera::update(float tpf) {

}
