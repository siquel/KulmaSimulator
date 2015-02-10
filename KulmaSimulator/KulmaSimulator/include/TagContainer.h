#pragma once
#include <vector>
#include <string>
#include <algorithm>

class TagContainer {
private:
	std::vector<std::string> tags;

	int indexOf(const std::string& tag) const;
public:
	TagContainer();

	bool isTagged(const std::string& tag) const;
	bool unTag(const std::string& tag);
	bool tag(const std::string& tag);

	~TagContainer();
};

