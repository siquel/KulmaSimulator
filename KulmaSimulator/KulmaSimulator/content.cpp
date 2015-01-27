#include "content.h"

ContentManager::ContentManager() { }
ContentManager::~ContentManager() { }

template <class T>
T* ContentManager::load(std::string asset) {
	return nullptr;
}