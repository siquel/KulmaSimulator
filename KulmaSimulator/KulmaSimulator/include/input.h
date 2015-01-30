#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "triggers.h"
#include <string>
#include <functional>
#include <map>
#include <string>
#include <vector>

class Mapping {
private:
	std::string name;
public:
	Mapping(std::string name);
	~Mapping();
};

class InputArgs {
public:
	InputArgs() {}
	~InputArgs(){}
};

typedef std::function<void(InputArgs*)> InputEvent;

class InputManager {
private:
	std::map<int, Mapping*> bindings;
	std::map<std::string, Mapping*> mappings;

public:
	InputManager();
	~InputManager();
	void bind(std::string name, std::function<void(InputArgs*)> args, std::vector<ITrigger*> triggers);
	bool hasMapping(std::string name);
	Mapping* getMapping(std::string name);
};

#endif