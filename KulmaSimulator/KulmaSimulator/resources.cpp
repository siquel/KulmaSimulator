#include "resources.h"
#include <iostream>
#include <fstream>
Resource::Resource() {

}

Resource::~Resource() {

}

Texture::Texture() : width(0), height(0) {

}

Texture::~Texture() {

}

bool Texture::readFromFile(const std::string& path) {
	// we only accept pngs
	std::string fullpath(path + ".png");
	std::vector<unsigned char> png;

	lodepng::load_file(png, fullpath);
	std::vector<unsigned char> pixels;
	size_t error = lodepng::decode(pixels, width, height, png.data(), png.size());

	if (error) {
		std::fprintf(stderr, "Error loading texture file %s\n", lodepng_error_text(error));
		return false;
	}
	return true;
}


