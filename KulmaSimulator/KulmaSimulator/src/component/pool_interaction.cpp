#include "component/pool_interaction.h"
#include "simulator.h"
#include "gamestate/pool.h"
PoolInteraction::PoolInteraction() {

}

PoolInteraction::~PoolInteraction() {

}

void PoolInteraction::interact(Entity* initiator) {
	Simulator::getInstance().doNextFrame([]() {
		Simulator::getInstance().getStateManager().change(new PoolState);
	});
}
