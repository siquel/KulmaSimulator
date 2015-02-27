#include "engine/camera.h"
#include <gl/glew.h>
#include <SDL/sdl.h>
#include <iostream>

#include "simulator.h"

const float Camera::MovementSpeedFactor = 0.3f;

Camera::Camera(float fov, float ar, float near, float far) :
	projection(glm::perspective(fov, ar, near, far)),
	midWinX(640), midWinY(720 / 2), position(1.f, 1.f, 0.f), rotation(0.f) { 
	InputManager& input = Simulator::getInstance().getInput();
	using namespace std::placeholders;
	input.bind("_CameraForward", std::bind(&Camera::moveForward, this, _1), 2, new KeyTrigger(SDLK_w), new KeyTrigger(SDLK_UP));
	input.bind("_CameraBackward", std::bind(&Camera::moveBackward, this, _1), 2, new KeyTrigger(SDLK_s), new KeyTrigger(SDLK_DOWN));
	//input.bind("_CameraStrafeLeft", std::bind(&Camera::strafeLeft, this, _1), 2, new KeyTrigger(SDLK_a), new KeyTrigger(SDLK_LEFT));
	//input.bind("_CameraStrafeRight", std::bind(&Camera::strafeRight, this, _1), 2, new KeyTrigger(SDLK_d), new KeyTrigger(SDLK_RIGHT));
}

void Camera::moveForward(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	float x, y, z;
	x = y = z = 0.f;

	float pitch = cosf(glm::radians(rotation.x));
	x = (MovementSpeedFactor * sinf(glm::radians(rotation.y))) * pitch;
	y = MovementSpeedFactor * sinf(glm::radians(rotation.x)) * -1.0f;
	float yaw = cosf(glm::radians(rotation.x));
	z = ((MovementSpeedFactor)* cosf(glm::radians(rotation.y)) * -1.0f) * yaw;

	speed.x += x;
	speed.y += y;
	speed.z += z;
}

void Camera::moveBackward(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	float z, y, x;
	x = y = z = 0.f;
	float pitch = cosf(glm::radians(rotation.x));
	x = MovementSpeedFactor * sinf(glm::radians(rotation.y)) * -1.0f * pitch;
	y = MovementSpeedFactor * sinf(glm::radians(rotation.x));
	float yaw = cosf(glm::radians(rotation.x));
	z = MovementSpeedFactor * cosf(glm::radians(rotation.y)) * yaw;
	speed.x += x;
	speed.y += y;
	speed.z += z;

}

Camera::~Camera() {}
const glm::mat4 Camera::getCamera() const {
	glm::mat4 rot;
	rot = glm::rotate(rot, rotation.x, glm::vec3(1.f, 0.f, 0.f));
	rot = glm::rotate(rot, rotation.y, glm::vec3(0.f, 1.f, 0.f));
	rot = glm::rotate(rot, rotation.z, glm::vec3(0.f, 0.f, 1.f));

	glm::vec3 forward = glm::vec3(rot[0][2], rot[1][2], rot[2][2]);
	glm::vec3 up(rot[0][1], rot[1][1], rot[2][1]);
	glm::vec3 right(rot[0][0], rot[1][0], rot[2][0]);
	forward = glm::normalize(forward);
	up = glm::normalize(up);
	right = glm::normalize(right);
	

	return projection * rot * glm::translate(-position);
}

void Camera::update(float tpf) {
	static const GLfloat verticalMouseSensitivy = 1000.0f;
	static const GLfloat horizlMouseSensitivy = 1000.0f;
	int mouseX, mouseY;
	mouseX = mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	int horizMovement = mouseX - midWinX;
	int vertMovement = mouseY - midWinY;

	rotation.x += vertMovement / verticalMouseSensitivy;
	rotation.y += horizMovement / horizlMouseSensitivy;

	// limit lookin up and down
	if (rotation.x < -90.f) {
		rotation.x = -90.f;
	}
	else if (rotation.x > 90.f) {
		rotation.x = 90.f;
	}

	// left and right
	if (rotation.y < -180.f) {
		rotation.y += 360.f;
	}
	else if (rotation.y > 180.f) {
		rotation.y -= 360.f;
	}
	


	// cap speed
	if (speed.x > MovementSpeedFactor) {
		speed.x = MovementSpeedFactor;
	}
	else if (speed.x < -MovementSpeedFactor) {
		speed.x = -MovementSpeedFactor;
	}

	if (speed.y > MovementSpeedFactor) {
		speed.y = MovementSpeedFactor;
	}
	else if (speed.y < -MovementSpeedFactor) {
		speed.y = -MovementSpeedFactor;
	}

	if (speed.z > MovementSpeedFactor) {
		speed.z = MovementSpeedFactor;
	}
	else if (speed.z < -MovementSpeedFactor) {
		speed.z = -MovementSpeedFactor;
	}

	position += speed;

	SDL_WarpMouseInWindow(Simulator::getInstance().getWindow(), midWinX, midWinY);
	std::cout << vertMovement << std::endl;
	

	// reset speed
	speed.x = speed.y = speed.z = 0.f;
}
