#include "engine/camera.h"
#include <gl/glew.h>
#include <SDL/sdl.h>
#include <iostream>

#include "simulator.h"

const float Camera::MovementSpeedFactor = 0.1f;

Camera::Camera(float fov, float ar, float near, float far) :
	projection(glm::perspective(fov, ar, near, far)),
	midWinX(640), midWinY(720 / 2), position(0.f, 0.f, 3.f), pitch(0.f), yaw(0.f) {
	InputManager& input = Simulator::getInstance().getInput();
	/*using namespace std::placeholders;
	input.bind("_CameraForward", std::bind(&Camera::moveForward, this, _1), 2, new KeyTrigger(SDLK_w), new KeyTrigger(SDLK_UP));
	input.bind("_CameraBackward", std::bind(&Camera::moveBackward, this, _1), 2, new KeyTrigger(SDLK_s), new KeyTrigger(SDLK_DOWN));
	input.bind("_CameraStrafeLeft", std::bind(&Camera::strafeLeft, this, _1), 2, new KeyTrigger(SDLK_a), new KeyTrigger(SDLK_LEFT));
	input.bind("_CameraStrafeRight", std::bind(&Camera::strafeRight, this, _1), 2, new KeyTrigger(SDLK_d), new KeyTrigger(SDLK_RIGHT));*/
}

void Camera::moveForward(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	position += MovementSpeedFactor * cameraFront;
}

void Camera::moveBackward(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	position -= MovementSpeedFactor * cameraFront;
}

void Camera::strafeLeft(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * MovementSpeedFactor;
}

void Camera::strafeRight(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	position += glm::normalize(glm::cross(cameraFront, cameraUp)) * MovementSpeedFactor;
}

Camera::~Camera() {}
const glm::mat4 Camera::getCamera() const {
	return projection * view;
}

void Camera::setView(glm::mat4& view) {
	this->view = view;
}

void Camera::update(float tpf) {
	/*
	static const GLfloat sensitivity = 0.05f;
	int mouseX, mouseY;
	mouseX = mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	int horizMovement = mouseX - midWinX;
	int vertMovement =  mouseY - midWinY;

	yaw += horizMovement * sensitivity;
	pitch += -vertMovement * sensitivity;

	if (pitch > 89.f) pitch = 89.f;
	if (pitch < -89.f) pitch = -89.f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	SDL_WarpMouseInWindow(Simulator::getInstance().getWindow(), midWinX, midWinY);
	position.y = 1.f;

	view = glm::lookAt(position, position + cameraFront, cameraUp);*/
}
