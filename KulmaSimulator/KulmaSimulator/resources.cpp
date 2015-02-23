#include "engine/resources.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include "util.h"
#include <algorithm>
#include <spritebatch.h>
#include <sstream>
#include "simulator.h"

Resource::Resource() {

}

Resource::~Resource() {

}

Texture::Texture() : Resource(), width(0), height(0) {

}

Texture::Texture(GLuint id, size_t w, size_t h) : id(id), width(w), height(h) {

}

Texture::~Texture() {
	glDeleteTextures(1, &id);
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
	// create new name for texture
	glGenTextures(1, &id);
	// bind it so we can modify it
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
	// set GL_NEAREST filter on
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// unbind
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

const GLuint& Texture::getId() const {
	return id;
}

bool Effect::readFromFile(const std::string& path) {
	std::string vertex(path + ".vert");
	std::string fragment(path + ".frag");
	program = compileShaders(readFile(vertex).c_str(), readFile(fragment).c_str());
	return true;
}

std::string Effect::readFile(const std::string& filepath) {
	std::ifstream fileStream(filepath, std::ios::binary);
	assert(fileStream.good());

	fileStream.seekg(0u, std::ios::end);
	std::string source;
	source.reserve(static_cast<unsigned int>(fileStream.tellg()));
	fileStream.seekg(0u, std::ios::beg);
	source.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
	assert(fileStream.good());

	return source;
}

GLuint Effect::compileShaders(const char* vertexSrc, const char* fragmentSrc) {
	GLint result = GL_FALSE;
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// create vertexshader
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	assert(result == GL_TRUE);

	// create fragment shader
	glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	assert(result == GL_TRUE);

	GLuint program = glCreateProgram();
	assert(program != 0);
	// attach shaders
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);


	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	assert(result == GL_TRUE);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}

void Effect::bind() const {
	glUseProgram(program);
	glAssert();
}

void Effect::unbind() const {
	glUseProgram(0);
}

GLuint Effect::getProgram() const {
	return program;
}

Effect::~Effect() {
	glDeleteProgram(program);
}

Effect::Effect() : program(0) { }

Font::Font() : texture(nullptr), spacing(20.f) {}
Font::~Font() {
}

bool Font::readFromFile(const std::string& path) {
	FT_Library lh;
	if (FT_Init_FreeType(&lh)) {
		fprintf(stderr, "Could not init freetype library\n");
		return false;
	}
	// TODO other types?
	std::string fullpath(path + ".ttf");

	// holds info about font
	FT_Face face;
	// load font
	if (FT_New_Face(lh, fullpath.c_str(), 0, &face)) {
		fprintf(stderr, "FT_New_Face failed, there is propably a problem with your font file");
		return false;
	}
	// TODO get this from somewhere else
	FT_Set_Pixel_Sizes(face, 0, 48);

	FT_GlyphSlot g = face->glyph;
	// get the width of atlas
	int widt, rows;
	widt = rows = 0;
	// as we only support ASCII, 32 is space and 127 is DEL
	for (size_t i = 32; i < 128; i++) {
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
			fprintf(stderr, "Loading character '%c' from %s failed\n", i, fullpath.c_str());
		}
		widt += g->bitmap.width;
		rows = std::max(rows, g->bitmap.rows);
	}
	// TODO this may fail?
	spacing = static_cast<float>(rows);
	// create empty texture for all characters
	GLuint texture;
	glActiveTexture(GL_TEXTURE0);
	glAssert();
	glGenTextures(1, &texture);
	glAssert();
	glBindTexture(GL_TEXTURE_2D, texture);
	glAssert();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// disable 4-byte alignment restrictions
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glAssert();
	// fill w/ empty data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, widt, rows, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	glAssert();
	int x = 0;
	// fill texture now
	for (size_t i = 32; i < 128; i++) {
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
			continue;

		info[i].ax = static_cast<float>(g->advance.x >> 6);
		info[i].ay = static_cast<float>(g->advance.y >> 6);

		info[i].bw = static_cast<float>(g->bitmap.width);
		info[i].bh = static_cast<float>(g->bitmap.rows);

		info[i].bl = static_cast<float>(g->bitmap_left);
		info[i].bt = static_cast<float>(g->bitmap_top);

		info[i].tx = static_cast<float>(x);

		// upload data from glyph
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
		glAssert();
		// increase x offset
		x += g->bitmap.width;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glAssert();
	this->texture.reset(new Texture(texture, static_cast<size_t>(widt), static_cast<size_t>(rows)));
	return true;
}

void Font::drawString(SpriteBatch& spriteBatch, std::string& str, glm::vec2& position, glm::vec4& color, float rotation, glm::vec2& origin, glm::vec2& scale) {
	std::unique_ptr<Texture>& tex = texture;
	forEachChar(str, [&](CharacterInfo& glyph, float x, float y) {
		glm::vec4 rect(glyph.tx, tex.get()->height - glyph.bh, glyph.bw, glyph.bh);
		
		glm::vec2 pos(position.x + x, position.y + y);
		spriteBatch.draw(tex.get(), pos, &rect, color, scale, origin, rotation);
	});
	//spriteBatch.draw(tex.get(), position, nullptr, color, scale, origin, rotation);
	glAssert();
}

void Font::forEachChar(const std::string& str, FontAction action) {
	float x = 0.f, y = 0.f;

	const char* text = str.c_str();
	char c;
	for (; *text; text++) {
		c = *text;
		switch (c) {
		case '\n':
			x = 0.f;
			y += spacing;
			break;
		default:
			CharacterInfo& glyph = info[c];

			if (!iswspace(c)) {
				action(glyph, x, y);
			}

			x += glyph.ax;
			break;
		}
	}
}


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
				materials = Mtllib::import(path.substr(0, index + 1) + file);
			}
			else {
				materials = Mtllib::import(file);
			}
			continue;
		}

		if (prefix == "usemtl") {
			std::string material;
			ss >> material;
			for (size_t i = 0; i < materials.size(); i++) {
				if (materials[i].getName() != material) continue;
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


std::vector<Material> Mtllib::import(const std::string& file) {
	std::ifstream in(file);
	assert(in.is_open());
	std::string line;
	std::string prefix;
	std::stringstream ss;

	std::vector<Material> materials;
	// as we increase it later to 0
	int current = -1;

	while (!in.eof()) {
		std::getline(in, line);
		ss.clear(); ss.str(""); prefix.clear();
		ss << line;
		ss >> prefix;
		// TODO what now?
		if (prefix == "newmtl") {
			std::string name;
			ss >> name >> std::ws;
			materials.push_back(Material(name));
		}
		else if (prefix == "Kd") {
			float r, g, b;
			ss >> r >> g >> b >> std::ws;
			materials.back().setDiffuseColor(r, g, b);
		}
		else if (prefix == "Ks") {
			float r, g, b;
			ss >> r >> g >> b >> std::ws;
			materials.back().setSpecularColor(r, g, b);
		}
		else if (prefix == "map_Kd") {
			std::string path;
			ss >> path >> std::ws;
			// get rid of content dir
			std::string fullpath(file.substr(Simulator::getInstance().getContent().getRoot().length() + 1));
			// get dirname
			fullpath.erase(std::find(fullpath.rbegin(), fullpath.rend(), '\\').base(), fullpath.end());
			// add original filename
			fullpath += path.substr(0, path.find('.'));
			
			materials.back().setTextureMap(Simulator::getInstance().getContent().load<Texture>(fullpath));
		}
	}
	return materials;
}