#ifndef CONTENT_H
#define CONTENT_H
#include <string>

class ContentManager {
public:
	ContentManager();
	~ContentManager();
	template <class T>
	T* load(std::string asset);
};

#endif