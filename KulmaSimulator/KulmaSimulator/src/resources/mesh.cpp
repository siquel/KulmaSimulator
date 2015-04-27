#include "resources/mesh.h"
#include <fstream>
#include <sstream>
#include "GLM.h"
#include "simulator.h"

Mesh::Mesh() {}
Mesh::~Mesh() {}

bool Mesh::readFromFile(const std::string& path) {
	std::string fullpath(path + ".obj");

	std::ifstream in(fullpath);
	if (!in.is_open()) return false;

	std::vector<GLuint> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tmpVertices, tmpNormals;
	std::vector<glm::vec2> tmpUvs;

	std::string line;
	std::string prefix;
	std::stringstream ss;

	size_t currentMaterial = 0;

	while (!in.eof()) {
		std::getline(in, line);
		ss.str(""); ss.clear();
		ss << line;
		ss >> prefix >> std::ws;
		// todo move this
		if (prefix == "mtllib") {
			std::string file;
			ss >> file;
			size_t index = path.rfind("\\");
			if (index != std::string::npos) {
				textures = Mtllib::import(path.substr(0, index + 1) + file);
			}
			else {
				textures = Mtllib::import(file);
			}
			continue;
		}

		if (prefix == "usemtl") {
			std::string material;
			ss >> material;
			for (size_t i = 0; i < textures.size(); i++) {
				//if (textures[i].getName() != material) continue;
				currentMaterial = i;
				break;
			}
		}
		else if (prefix == "v") {
			//vertex
			glm::vec3 v;
			ss >> v.x >> v.y >> v.z >> std::ws;
			tmpVertices.push_back(v);
		}
		else if (prefix == "vt") {
			// texture coord
			glm::vec2 uv;
			ss >> uv.x >> uv.y >> std::ws;
			tmpUvs.push_back(uv);
		}
		else if (prefix == "vn") {
			// normal
			glm::vec3 v;
			ss >> v.x >> v.y >> v.z >> std::ws;
			tmpNormals.push_back(v);
		}
		else if (prefix == "f") {
			// index
			for (size_t i = 0; i < 3; i++) {
				GLuint v, t, n;
				char c;

				ss >> v >> c >> t >> c >> n >> std::ws;
				vertexIndices.push_back(v);
				uvIndices.push_back(t);
				normalIndices.push_back(n);
			}
		}
	}

	// f = v/vt/vn
	for (size_t i = 0; i < vertexIndices.size(); i++) {
		size_t index = vertexIndices[i];
		glm::vec3& vertex = tmpVertices[index - 1];
		vertices.push_back(vertex.x);
		vertices.push_back(vertex.y);
		vertices.push_back(vertex.z);
		index = uvIndices[i];
		glm::vec2& uv = tmpUvs[index - 1];
		vertices.push_back(uv.x);
		vertices.push_back(uv.y);
		index = normalIndices[i];
		// hax TODO fix
		if (tmpNormals.size() == 0) {
			vertices.push_back(0.f);
			vertices.push_back(0.f);
			vertices.push_back(0.f);
		}
		else {
			glm::vec3& normal = tmpNormals[index - 1];
			vertices.push_back(normal.x);
			vertices.push_back(normal.y);
			vertices.push_back(normal.z);
		}

	}
	return true;
}

const std::vector<GLfloat>& Mesh::getVertices() const {
	return vertices;
}

const std::vector<Texture*>& Mesh::getTextures() const {
	return textures;
}


std::vector<Texture*> Mtllib::import(const std::string& file) {
	std::ifstream in(file);
	assert(in.is_open());
	std::string line;
	std::string prefix;
	std::stringstream ss;

	std::vector<Texture*> textures;
	// as we increase it later to 0
	int current = -1;

	while (!in.eof()) {
		std::getline(in, line);
		ss.clear(); ss.str(""); prefix.clear();
		ss << line;
		ss >> prefix;
		if (prefix == "map_Kd") {
			std::string path;
			ss >> path >> std::ws;
			// get rid of content dir
			std::string fullpath(file.substr(Simulator::getInstance().getContent().getRoot().length() + 1));
			// get dirname
			fullpath.erase(std::find(fullpath.rbegin(), fullpath.rend(), '\\').base(), fullpath.end());
			// add original filename
			fullpath += path.substr(0, path.find('.'));

			textures.push_back(Simulator::getInstance().getContent().load<Texture>(fullpath));
		}
	}
	return textures;
}