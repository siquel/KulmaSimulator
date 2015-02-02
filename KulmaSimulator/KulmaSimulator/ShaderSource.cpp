/**
* @file ShaderSource.cpp
*
* OpenGL Template
*/

#include <cassert>
#include <fstream>
#include <ShaderSource.h>

using namespace std;

// Public

// Static

string ShaderSource::load(const string& filepath)
{
	ifstream fileStream(filepath, ios::binary);
	assert(fileStream.good());

	fileStream.seekg(0u, ios::end);
	string source;
	source.reserve(static_cast<unsigned int>(fileStream.tellg()));
	fileStream.seekg(0u, ios::beg);
	source.assign(istreambuf_iterator<char>(fileStream), istreambuf_iterator<char>());
	assert(fileStream.good());

	return source;
}