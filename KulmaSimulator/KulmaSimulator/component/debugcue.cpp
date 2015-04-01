#include "component\debugcue.h"
#include "simulator.h"
#include "Entity.h"
#include "component/rigidbody.h"
DebugCueBall::DebugCueBall() : Component(0) { enable(); }
DebugCueBall::~DebugCueBall() {}

void DebugCueBall::onInitialize() {
	using namespace std::placeholders;
	InputManager& input = Simulator::getInstance().getInput();
	input.bind("shoot", std::bind(&DebugCueBall::shoot, this, _1), 1, new KeyTrigger(SDLK_SPACE));
}

void DebugCueBall::shoot(InputArgs& args) {
	if (args.state != RELEASED) return;
	Rigidbody* body = getOwner()->getComponent<Rigidbody>();
	body->getBody()->ApplyLinearImpulse(b2Vec2(0, -10.f), body->getBody()->GetWorldCenter(), true);
}