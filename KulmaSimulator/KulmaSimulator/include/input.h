#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "triggers.h"
#include <string>
#include <functional>
#include <map>
#include <string>
#include <vector>

enum InputState {
	PRESSED,
	DOWN,
	RELEASED,
	UP
};

// sent to callback
struct InputArgs {
	InputState state;
};
// used as callback when binding is pressed/released/down
typedef std::function<void(InputArgs)> InputEvent;

// represents class that holds triggers which can invoke callback func
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
// runs the input system
class InputManager {
private:
	// has mappings as SDL_Keycode so we can check if they're pressed
	std::vector<int> binds;
	// contains mapping names for specific SDL_Keycode
	std::map<int, std::vector<std::string>> bindings;
	// links all the callbacks to binding name
	std::map<std::string, Mapping*> mappings;
	// maps trigger to all three containers
	void mapTrigger(std::string mappingName, ITrigger* trigger);
	std::vector<InputListener*> listeners;
public:
	InputManager();
	~InputManager();
	// creates new binding for keys, there should be at least one key
	void bind(std::string name, InputEvent args, std::vector<ITrigger*> triggers);
	// checks if the binding name has any mappings on it
	bool hasMapping(std::string name);
	
	Mapping* getMapping(std::string name);
	// updates all the listeners and buffers 
	void update();
	const std::vector<int>& getBinds() const;
	const std::vector<std::string>& getMappingNames(SDL_Keycode key) const;
};

class KeyInputListener;
class InputBuffer {
private:
	// resolves all mappings names for specific key
	void resolveMappings(std::map<std::string, Mapping*>* map, InputManager*, SDL_Keycode key);
public:
	// which bindings are currently down
	std::map<std::string, Mapping*> down;
	std::map<std::string, Mapping*> released;
	std::map<std::string, Mapping*> pressed;
	InputBuffer();
	~InputBuffer();
	// clears the buffer and fills it again if necessary
	void update(InputManager*, KeyInputListener*);
};

// abstract class to hold listeners, extend this if we need eg. gamepad or mouse support
class InputListener {
protected:
	InputBuffer buffer;
public:
	InputListener();
	~InputListener();
	virtual void update(InputManager*) = 0;
};

// listens keyboard events 
class KeyInputListener : public InputListener {
public:
	// don't free this, it's valid for whole run time
	const Uint8* state;
	// SDL doesn't offer previous state, so we gotta do little hax to be able to 
	// see if key was just pressed or released
	std::map<SDL_Keycode, int> lastState;
	KeyInputListener();
	~KeyInputListener();
	// fetches all triggered mappings from buffers and invokes callbacks
	void update(InputManager* mgr);
};

#endif