#include "component/player_controller.h"
#include "simulator.h"
#include "engine/input.h"
PlayerController::PlayerController() {

}

PlayerController::~PlayerController() {

}

void PlayerController::onInitialize() {
	InputManager& input = Simulator::getInstance().getInput();
}
void PlayerController::onUpdate(float tpf) {

}