#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Component.h"
class PlayerController : public Component {
public:
	PlayerController();
	~PlayerController();
protected:
	void onInitialize();
	void onUpdate(float tpf);
};

#endif