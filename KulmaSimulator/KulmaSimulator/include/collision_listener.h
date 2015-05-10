#pragma once

#include <Box2D/Box2D.h>
#include <vector>

class CollisionListener {
public:
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
};

class ContactListener : public b2ContactListener {
private:
	std::vector<CollisionListener*> listeners;
public:
	ContactListener() = default;
	~ContactListener();
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void addListener(CollisionListener* listener);
	void removeListener(CollisionListener* listener);
};