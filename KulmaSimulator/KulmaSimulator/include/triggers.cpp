#include "triggers.h"

ITrigger::ITrigger() { }
ITrigger::~ITrigger() { }



KeyTrigger::KeyTrigger() { }
KeyTrigger::~KeyTrigger() { }
int KeyTrigger::triggerHash() { return 0;  }

bool operator==(const KeyTrigger& lhs, const KeyTrigger& rhs) {
	return false;
}

bool operator!=(const KeyTrigger& lhs, const KeyTrigger& rhs) {
	return false;
}