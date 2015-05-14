#pragma once
#include "component/interaction.h"
class PoolInteraction : public InteractionComponent {
public:
	PoolInteraction();
	~PoolInteraction();
	void interact(Entity* initiator) override;
};