#include "engine/content.h"

ContentManager::ContentManager(const std::string& rootDirectory = "Content") : root(rootDirectory)
{
	// get rid of path seperator
	std::size_t index = root.rfind("\\", root.length() - 1);
	if (index != std::string::npos) {
		root.erase(index, 1);
	}
}
ContentManager::~ContentManager() { }

bool ContentManager::isLoaded(std::string& asset) const {
	return assets.find(asset) != assets.end();
}

const std::string& ContentManager::getRoot() const {
	return root;
}

void ContentManager::unload(const std::string& asset) {

}

void ContentManager::unloadAll() {

}
