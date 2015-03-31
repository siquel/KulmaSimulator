#pragma once
#include "Component.h"
struct InputArgs;
class DebugCueBall : public Component {
public:
	DebugCueBall();
	~DebugCueBall();
protected:
	void onInitialize() override;
private:
	void shoot(InputArgs& args);
};