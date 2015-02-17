#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H
#include "Component.h"
#include "engine/input.h"
class InputComponent : public Component {
public:
	InputComponent();
	~InputComponent();
protected:
	void onInitialize();

private:
	void moveRight(InputArgs& args);
	void moveLeft(InputArgs& args);
	void moveUp(InputArgs& args);
	void moveDown(InputArgs& args);
};

#endif