#include "input.h"
#include "exceptions.h"
InputManager::InputManager() { }
InputManager::~InputManager() { }

void InputManager::bind(std::string name, ITrigger* trigger, ...) {
	va_list args;
	va_start(args, trigger);
	//ITrigger* t = va_arg(args, ITrigger*);
	throw NotImplementedException();
	va_end(args);
}