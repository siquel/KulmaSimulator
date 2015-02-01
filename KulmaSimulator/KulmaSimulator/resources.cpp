#include "resources.h"
#include <iostream>
Resource::Resource() {

}

Resource::~Resource() {

}

Texture::Texture() : width(0), height(0) {

}

Texture::~Texture() {

}

bool Texture::readFromFile(const std::string& path) {
	std::cout << path << std::endl;
	return false;
}


