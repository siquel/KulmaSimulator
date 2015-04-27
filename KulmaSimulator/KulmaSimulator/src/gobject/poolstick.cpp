#include "component/poolstick.h"
#include "simulator.h"
#include "component/transform.h"
#include "component/rigidbody.h"
#include "Entity.h"
PoolStick::PoolStick(Entity* cueball) 
	: midWinX(Game::WINDOW_WIDTH / 2), midWinY(Game::WINDOW_HEIGHT / 2), 
	pitch(0.f), yaw(0.f), up(glm::vec3(0.0f, 1.0f, 0.0f)), cueball(cueball), forward(0.f, 0.f,0.f) {
	enable();
}

void PoolStick::onInitialize() {
	using namespace std::placeholders;
	InputManager& input = Simulator::getInstance().getInput();
	input.bind("shoot", std::bind(&PoolStick::shoot, this, _1), 1, new KeyTrigger(SDLK_SPACE));
}
void PoolStick::shoot(InputArgs& args) {
	if (args.state != PRESSED) return;
	Rigidbody* body = cueball->getComponent<Rigidbody>();
	const glm::vec3& forward = getForwardVector();
	body->getBody()->ApplyLinearImpulse(b2Vec2(-forward.x, -forward.z), body->getBody()->GetWorldCenter(), true);
}
void PoolStick::onUpdate(float tpf) {
	Camera& camera = Simulator::getInstance().getCamera();

	static const GLfloat sensitivity = 0.05f;
	int mouseX, mouseY;
	mouseX = mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	int horizMovement = mouseX - midWinX;
	int vertMovement = mouseY - midWinY;

	yaw += horizMovement * sensitivity;
	pitch += -vertMovement * sensitivity;

	if (pitch > 89.f) pitch = 89.f;
	if (pitch < -30.f) pitch = -30.f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->forward = glm::normalize(front);
	SDL_WarpMouseInWindow(Simulator::getInstance().getWindow(), midWinX, midWinY);

	Transform* tf = cueball->getComponent<Transform>();
	glm::vec3 position = tf->getPosition();

	glm::mat4 rot = glm::rotate(atan2f(front.x, front.z), glm::vec3(0.f, 1.f, 0.f));
	rot *= glm::rotate(glm::radians(-10.f), glm::vec3(1, 0, 0));
	Transform* mytf = getOwner()->getComponent<Transform>();
	mytf->setPosition(position);
	mytf->setRotation(rot);


	position.y = 1.5f;

	camera.setView(glm::lookAt(position + glm::normalize(front), tf->getPosition(), up));
}

const glm::vec3& PoolStick::getForwardVector() const {
	return forward;
}