#pragma once

#include "Component.h"
// class that represents a action which is made by someone request eg. player
class InteractionComponent : public Component
{
public:
	InteractionComponent();
	virtual ~InteractionComponent();
	virtual void interact(Entity* initiator) = 0;
protected:
	
private:
};