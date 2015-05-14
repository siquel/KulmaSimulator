#include "component/player_controller.h"
#include "simulator.h"
#include "engine/input.h"
#include "component/transform.h"
#include "Entity.h"
#include "component/rigidbody.h"
#include "component/interaction.h"

class InteractionCallback : public b2RayCastCallback {
public:
	Entity* result = nullptr;
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override {
		if (fixture->GetUserData()) {
			Entity* entity =static_cast<Entity*>(fixture->GetUserData());

			// is player
 			if (entity->getComponent<PlayerController>()) {
				return -1;
			}
			result = entity;
			// gotta find the closest
			return fraction;
		}
		// not having entity so we dont need it
		return -1;
	}
};

PlayerController::PlayerController() {
	enable();
}

PlayerController::~PlayerController() {
	InputManager& input = Simulator::getInstance().getInput();
	input.unbind("Move forward");
	input.unbind("Move backward");
	input.unbind("Move left");
	input.unbind("Move right");
	input.unbind("Interact");
}

void PlayerController::onInitialize() {
	InputManager& input = Simulator::getInstance().getInput();
	using namespace std::placeholders;
	input.bind("Move forward", KULMA_INPUT_BIND_2(PlayerController::moveForward, this, new KeyTrigger(SDLK_w), new KeyTrigger(SDLK_UP)));
	input.bind("Move backward", KULMA_INPUT_BIND_2(PlayerController::moveBackward, this, new KeyTrigger(SDLK_s), new KeyTrigger(SDLK_DOWN)));
	input.bind("Move left", KULMA_INPUT_BIND_2(PlayerController::strafeLeft, this, new KeyTrigger(SDLK_a), new KeyTrigger(SDLK_LEFT)));
	input.bind("Move right", KULMA_INPUT_BIND_2(PlayerController::strafeRight, this, new KeyTrigger(SDLK_d), new KeyTrigger(SDLK_RIGHT)));
	input.bind("Interact", KULMA_INPUT_BIND_1(PlayerController::interact, this, new KeyTrigger(SDLK_SPACE)));
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
	DynamicBody* body = getOwner()->getComponent<DynamicBody>();
	body->getBody()->ApplyLinearImpulse(b2Vec2(-forward.x, -forward.z), body->getBody()->GetWorldCenter(), true);
}

void PlayerController::strafeLeft(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	glm::vec3 dir = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
	DynamicBody* body = getOwner()->getComponent<DynamicBody>();
	body->getBody()->ApplyLinearImpulse(-b2Vec2(dir.x, dir.z), body->getBody()->GetWorldCenter(), true);
}

void PlayerController::strafeRight(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	glm::vec3 dir = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));
	DynamicBody* body = getOwner()->getComponent<DynamicBody>();
	body->getBody()->ApplyLinearImpulse(b2Vec2(dir.x, dir.z), body->getBody()->GetWorldCenter(), true);
}

void PlayerController::interact(InputArgs& args) {
	if (args.state != InputState::PRESSED) return;
	//b2RayCastCallback callback;
	const b2World* world = getOwner()->getComponent<Rigidbody>()->getBody()->GetWorld();
	Transform *tx = getOwner()->getComponent<Transform>();
	const glm::vec3 me = tx->getPosition();
	// fov is 2f
	const glm::vec3 to = me + forward * 2.f;
	InteractionCallback cb;
	world->RayCast(&cb, b2Vec2(me.x, me.z), b2Vec2(to.x, to.z));

	// we didnt hit anyone
	if (!cb.result) {
 		return;
	}

	InteractionComponent* ic = cb.result->getComponent<InteractionComponent>();
	ic->interact(getOwner());
}
