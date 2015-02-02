#include "input.h"
#include "exceptions.h"
#include <iostream>
#include <algorithm>
InputManager::InputManager() { 
	listeners.push_back(new KeyInputListener());
}
InputManager::~InputManager() {
	std::for_each(listeners.begin(), listeners.end(), [](InputListener* listener) {
		delete listener;
	});
	listeners.clear();
	for (std::map<std::string, Mapping*>::iterator it = mappings.begin(); it != mappings.end(); it++) {
		delete it->second;
	}
	mappings.clear();

}

void InputManager::bind(std::string name, InputEvent event, std::vector<ITrigger*> triggers) {

	Mapping* mapping = getMapping(name);
	if (mapping == nullptr) {
		 mapping = new Mapping(name, event);
		 mappings[name] = mapping;
	}
	else {
		throw std::logic_error("There is already mapping");
	}

	if (triggers.size() == 0) {
		throw std::logic_error("There need to be at least 1 trigger");
	}
	
	std::vector<ITrigger*>::iterator it;
	for (it = triggers.begin(); it != triggers.end(); it++) {
		mapTrigger(name, (*it));
		mapping->addTrigger(*it);
		binds.push_back((*it)->triggerHash());
	}
	

}

void InputManager::mapTrigger(std::string mappingName, ITrigger* trigger) {
	std::vector<std::string> names;
	// doesnt exists
	if (bindings.find(trigger->triggerHash()) == bindings.end()) {
		bindings[trigger->triggerHash()] = names;
	}

	std::vector<std::string>* ptr = &bindings[trigger->triggerHash()];
	if (std::find(ptr->begin(), ptr->end(), mappingName) == ptr->end()) {
		ptr->push_back(mappingName);
	}
	else {
		throw std::logic_error("Trying to map " + mappingName + " twice");
	}
}

void InputManager::update() {
	for (size_t i = 0; i < listeners.size(); i++) {
		listeners[i]->update(this);
	}
	
}

const std::vector<int>& InputManager::getBinds() const {
	return binds;
}


bool InputManager::hasMapping(std::string name) {
	return mappings.find(name) != mappings.end();
}

Mapping* InputManager::getMapping(std::string name) {
	if (hasMapping(name)) return mappings[name];
	return nullptr;
}

const std::vector<std::string>& InputManager::getMappingNames(SDL_Keycode key) const {
	return bindings.at(key);
}

Mapping::Mapping(std::string name, InputEvent event) : name(name), event(event) {
	
}

Mapping::~Mapping() {
	std::for_each(triggers.begin(), triggers.end(), [](ITrigger* t) {
		delete t;
	});
	triggers.clear();
}

const std::string& Mapping::getName() const {
	return name;
}

void Mapping::addTrigger(ITrigger* trigger) {
	triggers.push_back(trigger);
}


InputBuffer::InputBuffer() {}
InputBuffer::~InputBuffer() { }

void InputBuffer::update(InputManager* mgr, KeyInputListener* keyinput) {
	down.clear();
	released.clear();
	pressed.clear();
	// last state has all the keys which are mapped
	for (std::map<SDL_Keycode, int>::iterator it = keyinput->lastState.begin();
		it != keyinput->lastState.end(); it++) {
		SDL_Keycode key = it->first;
			
		int state = keyinput->state[SDL_GetScancodeFromKey(key)];
		// it's pressed
		if (keyinput->lastState[key] == 0 && state) {
			resolveMappings(&pressed, mgr, key);
		}
		 // it's down
		else if (state) {
				resolveMappings(&down, mgr, key);
		// it's released
		}
		else if (keyinput->lastState[key] == 1 && state == 0) {
			resolveMappings(&released, mgr, key);
		}
	}
}

void InputBuffer::resolveMappings(std::map<std::string, Mapping*>* list, InputManager* mgr, SDL_Keycode key) {
	const std::vector<std::string>& names = mgr->getMappingNames(key);
	std::for_each(names.begin(), names.end(), [mgr,list](const std::string& name) {
		list->insert(std::make_pair(name, mgr->getMapping(name)));
	});
}

InputListener::InputListener() {}
InputListener::~InputListener() {}

KeyInputListener::KeyInputListener() {
	state = SDL_GetKeyboardState(NULL);
}
KeyInputListener::~KeyInputListener() {}
void KeyInputListener::update(InputManager* mgr) {
	const std::vector<int>& binds = mgr->getBinds();
	for (size_t i = 0; i < binds.size(); i++) {
		SDL_Keycode key = binds[i];
		lastState[key] = state[SDL_GetScancodeFromKey(key)];		
	}
	SDL_PumpEvents();
	
	buffer.update(mgr, this);
	for (auto it = buffer.down.begin(); it != buffer.down.end(); it++) {
		InputArgs args;
		args.state = InputState::DOWN;
		it->second->event(args);
	}

	for (auto it = buffer.released.begin(); it != buffer.released.end(); it++) {
		InputArgs args;
		args.state = InputState::RELEASED;
		it->second->event(args);
	}

	for (auto it = buffer.pressed.begin(); it != buffer.pressed.end(); it++) {
		InputArgs args;
		args.state = InputState::PRESSED;
		it->second->event(args);
	}
}