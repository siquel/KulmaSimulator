/**
* @file ShaderSource.h
*
* OpenGL Template
*/

#pragma once

#include <string>

class ShaderSource
{
public:

	static std::string load(const std::string& filepath);

private:

	ShaderSource() = delete;
	ShaderSource(const ShaderSource& shaderSource) = delete;
	ShaderSource(ShaderSource&& shaderSource) = delete;
	~ShaderSource() = delete;

	ShaderSource& operator =(const ShaderSource& shaderSource) = delete;
};