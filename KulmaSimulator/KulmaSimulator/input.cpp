#include "input.h"
#include "exceptions.h"
#include <iostream>
InputManager::InputManager() { }
InputManager::~InputManager() { }

void InputManager::bind(std::string name, InputEvent a, std::vector<ITrigger*> triggers) {

	Mapping* mapping = getMapping(name);
	if (mapping == nullptr) {
		 mapping = new Mapping(name);
		 mappings[name] = mapping;
	}
	else {
		throw std::logic_error("There is already mapping");
	}

	if (triggers.size() == 0) {
		throw std::logic_error("There need to be at least 1 trigger");
	}
	ITrigger* trig = nullptr;
	std::vector<ITrigger*>::iterator it;
	for (it = triggers.begin(); it != triggers.end(); it++) {
		std::cout << (*it)->triggerHash() << std::endl;
	}
	

}


bool InputManager::hasMapping(std::string name) {
	return mappings.find(name) != mappings.end();
}

Mapping* InputManager::getMapping(std::string name) {
	if (hasMapping(name)) return mappings[name];
	return nullptr;
}

Mapping::Mapping(std::string name) : name(name) {
	
}

Mapping::~Mapping() {

}

