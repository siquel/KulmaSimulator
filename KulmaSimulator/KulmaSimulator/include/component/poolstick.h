#pragma once

#include "DrawableComponent.h"
#include "engine/input.h"
class PoolStick : public DrawableComponent {
public:
	PoolStick(Entity* cueball);
	~PoolStick() = default;
	const glm::vec3& getForwardVector() const;
protected:
	void onInitialize() override;
	void onUpdate(float tpf) override;
private:
	void shoot(InputArgs& args);
	glm::vec3 up;
	glm::vec3 forward;

	int midWinX;
	int midWinY;

	float yaw;
	float pitch;

	Entity* cueball;
};