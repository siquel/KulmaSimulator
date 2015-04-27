#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
class Resource {
public:
	Resource();
	virtual ~Resource();
	virtual bool readFromFile(const std::string& path) = 0;
};
#endif