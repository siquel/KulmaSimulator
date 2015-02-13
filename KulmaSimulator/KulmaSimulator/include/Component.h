#pragma once
#include <cassert>

class Entity;

// Base class for components that can update.
class Component {
private:
	Entity& owner;

	int updateOrder;

	bool destroyed;
	bool enabled;
	bool initialized;
protected:
	Entity& getOwner() const;

	// Called every update if component is enabled.
	virtual void onUpdate(float tpf);

	// Called when component gets destroyed.
	virtual void onDestroyed();

	// Called when enabled value changes.
	virtual void onEnabledChanged(const bool oldState, const bool newState);

	// Called when update order changes.
	virtual void updateOrderChanged(const int newOrder, const int oldOrder);

	// Called in first enable call.
	virtual void onInitialize();
public:
	int getUpdateOrder() const;

	Component(Entity& owner, const int updateOrder = 0);

	void changeUpdateOrder(const int newOrder);

	void enable();
	void disable();
	bool isEnabled() const;

	void destroy();
	bool isDestroyed() const;

	void update(float tpf);

	virtual ~Component();
};