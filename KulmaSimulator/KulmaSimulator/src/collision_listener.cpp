#include "collision_listener.h"
#include "util.h"
ContactListener::~ContactListener() {

}

void ContactListener::BeginContact(b2Contact* contact) {
	for (size_t i = 0; i < listeners.size(); ++i) {
		listeners[i]->BeginContact(contact);
	}
}

void ContactListener::EndContact(b2Contact* contact) {
	for (size_t i = 0; i < listeners.size(); ++i) {
		listeners[i]->EndContact(contact);
	}
}

void ContactListener::addListener(CollisionListener* listener) {
	if (std::find(listeners.begin(), listeners.end(), listener) != listeners.end()) {
		LOG_INFO("trying to add listener more than once");
		return;
	}
	listeners.push_back(listener);
}

void ContactListener::removeListener(CollisionListener* listener) {
	listeners.erase(std::find(listeners.begin(), listeners.end(), listener));
}

void CollisionListener::BeginContact(b2Contact* contact) {}

void CollisionListener::EndContact(b2Contact* contact) {}
