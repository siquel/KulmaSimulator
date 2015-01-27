#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "triggers.h"
#include <string>

class InputManager {
public:
	InputManager();
	~InputManager();
	void bind(std::string name, ITrigger* trigger, ...);
};

#endif