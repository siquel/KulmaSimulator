#ifndef TRIGGERS_H
#define TRIGGERS_H

#include "SDL\SDL.h"

enum TriggerType {
	KEY_TRIGGER,
	BUTTON_TRIGGER
};

class ITrigger {
public:
	ITrigger();
	~ITrigger();
	virtual int triggerHash() = 0;
};

class KeyTrigger : public ITrigger {
public: 
	KeyTrigger();
	~KeyTrigger();
	int triggerHash();
};

#endif