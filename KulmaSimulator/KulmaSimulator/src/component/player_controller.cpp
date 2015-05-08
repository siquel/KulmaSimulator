#include "component/player_controller.h"
#include "simulator.h"
#include "engine/input.h"
#include "component/transform.h"
#include "Entity.h"
#include "component/rigidbody.h"

const float PlayerController::MovementSpeedFactor = 0.1f;
PlayerController::PlayerController() {
	enable();
}

PlayerController::~PlayerController() {

}

void PlayerController::onInitialize() {
	InputManager& input = Simulator::getInstance().getInput();
	using namespace std::placeholders;
	input.bind("Move forward", std::bind(&PlayerController::moveForward, this, _1), 2, new KeyTrigger(SDLK_w), new KeyTrigger(SDLK_UP));
	input.bind("Move backward", std::bind(&PlayerController::moveBackward, this, _1), 2, new KeyTrigger(SDLK_s), new KeyTrigger(SDLK_DOWN));
	input.bind("Move left", std::bind(&PlayerController::strafeLeft, this, _1), 2, new KeyTrigger(SDLK_a), new KeyTrigger(SDLK_LEFT));
	input.bind("Move right", std::bind(&PlayerController::strafeRight, this, _1), 2, new KeyTrigger(SDLK_d), new KeyTrigger(SDLK_RIGHT));
}
void PlayerController::onUpdate(float tpf) {
	static const GLfloat sensitivity = 0.05f;
	int mouseX, mouseY;
	mouseX = mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	int midWinX = Game::WINDOW_WIDTH / 2;
	int midWinY = Game::WINDOW_HEIGHT / 2;
	int horizMovement = mouseX - midWinX;
	int vertMovement = mouseY - midWinY;

	yaw += horizMovement * sensitivity;
	pitch += -vertMovement * sensitivity;

	if (pitch > 89.f) pitch = 89.f;
	if (pitch < -89.f) pitch = -89.f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(front);
	SDL_WarpMouseInWindow(Simulator::getInstance().getWindow(), midWinX, midWinY);
	Transform* tf = getOwner()->getComponent<Transform>();
	glm::vec3 position = tf->getPosition();
	position.y = 1.f;
	Simulator::getInstance().getCamera().setView(glm::lookAt(position, position + forward, glm::vec3(0,1,0)));
}

void PlayerController::moveForward(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	DynamicBody* body = getOwner()->getComponent<DynamicBody>();
	body->getBody()->ApplyLinearImpulse(b2Vec2(forward.x, forward.z), body->getBody()->GetWorldCenter(), true);
}

void PlayerController::moveBackward(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	position -= MovementSpeedFactor * forward;
}

void PlayerController::strafeLeft(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	position -= glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0))) * MovementSpeedFactor;
}

void PlayerController::strafeRight(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	position += glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0))) * MovementSpeedFactor;
}