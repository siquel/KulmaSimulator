#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "triggers.h"
#include <string>
#include <functional>
#include <map>
#include <string>
#include <vector>

class InputArgs {
public:
	InputArgs() {}
	~InputArgs(){}
};

typedef std::function<void(InputArgs*)> InputEvent;

class Mapping {
private:
	std::string name;
	std::vector<ITrigger*> triggers;
	
public:
	const InputEvent event;
	Mapping(std::string name, InputEvent event);
	void addTrigger(ITrigger*);
	const std::string& getName() const;
	~Mapping();
};

class InputListener;
class InputManager {
private:
	std::vector<int> binds;
	std::map<int, std::vector<std::string>> bindings;
	std::map<std::string, Mapping*> mappings;
	void mapTrigger(std::string mappingName, ITrigger* trigger);
	std::vector<InputListener*> listeners;
public:
	InputManager();
	~InputManager();
	void bind(std::string name, std::function<void(InputArgs*)> args, std::vector<ITrigger*> triggers);
	bool hasMapping(std::string name);
	Mapping* getMapping(std::string name);
	void update();
	const std::vector<int>& getBinds() const;
	const std::vector<std::string>& getMappingNames(SDL_Keycode key) const;
};

class KeyInputListener;
class InputBuffer {
private:
	void resolveMappings(std::map<std::string, Mapping*>* map, InputManager*, SDL_Keycode key);
public:
	std::map<std::string, Mapping*> down;
	InputBuffer();
	~InputBuffer();
	void update(InputManager*, KeyInputListener*);
};

class InputListener {
protected:
	InputBuffer buffer;
public:
	InputListener();
	~InputListener();
	virtual void update(InputManager*) = 0;
};

class KeyInputListener : public InputListener {
public:
	const Uint8* state;
	std::map<SDL_Keycode, int> lastState;
	KeyInputListener();
	~KeyInputListener();
	void update(InputManager* mgr);
};

#endif