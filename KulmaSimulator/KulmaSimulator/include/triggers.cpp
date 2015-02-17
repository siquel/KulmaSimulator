#include "engine/triggers.h"

ITrigger::ITrigger() { }
ITrigger::~ITrigger() { }

KeyTrigger::KeyTrigger(SDL_Keycode key) : key(key){
	
}
KeyTrigger::~KeyTrigger() { }
int KeyTrigger::triggerHash() { return key;  }

bool operator==(const KeyTrigger& lhs, const KeyTrigger& rhs) {
	return false;
}

bool operator!=(const KeyTrigger& lhs, const KeyTrigger& rhs) {
	return false;
}