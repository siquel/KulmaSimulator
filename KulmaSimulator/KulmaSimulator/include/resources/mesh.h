#ifndef MESH_H
#define MESH_H
#include <string>
#include <vector>
#include <gl/glew.h>
#include "resource.h"
class Texture;


class Material {
private:
	std::string name;
	// Kd from obj
	float diffuse[3];
	// Ks from obj
	float specular[3];
	const Texture* map;
public:
	Material(const std::string& name) : name(name), map(nullptr) {}
	bool readFromFile(const std::string& path);
	void setDiffuseColor(float r, float g, float b) {
		diffuse[0] = r; diffuse[1] = g; diffuse[2] = b;
	}
	void setSpecularColor(float r, float g, float b) {
		specular[0] = r; specular[1] = g; specular[2] = b;
	}
	void setTextureMap(const Texture* texture) {
		map = texture;
	}
	const std::string& getName() const {
		return name;
	}

	const Texture* getTexture() const {
		return map;
	}
};

class Mesh : public Resource {
private:
	std::vector<GLfloat> vertices;
	std::vector<Texture*> textures;
public:
	Mesh();
	~Mesh();
	bool readFromFile(const std::string& path);
	const std::vector<GLfloat>& getVertices() const;
	const std::vector<Texture*>& getTextures() const;
};

class Mtllib {
public:
	static std::vector<Texture*> import(const std::string& mtlfile);
};

#endif