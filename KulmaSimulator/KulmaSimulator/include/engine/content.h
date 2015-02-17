#ifndef CONTENT_H
#define CONTENT_H
#include <string>
#include <map>
#include <memory>
#include "resources.h"
class ContentManager {
private:
	std::string root;
	std::map<std::string, Resource*> assets;
	bool isLoaded(std::string& asset) const;
public:
	ContentManager(const std::string& rootDirectory);
	~ContentManager();

	template <class T>
	T* load(std::string asset) {
		if (isLoaded(asset)) return static_cast<T*>(assets[asset]);

		std::string path = root + "\\" + asset;
		T* resource = new T();
		if (!resource->readFromFile(path)) {
			// things went south
			throw std::runtime_error("Can't open file " + path + "!");
		}

		assets[asset] = resource;

		return static_cast<T*>(resource);
	};

	const std::string& getRoot() const;
	void unload(const std::string& asset);
	void unloadAll();
};

#endif