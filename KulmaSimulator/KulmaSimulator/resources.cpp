#include "engine/resources.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include "util.h"
#include <algorithm>
#include <spritebatch.h>
#include <sstream>

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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
	//glActiveTexture(GL_TEXTURE0);
	glAssert();
	glGenTextures(1, &texture);
	glAssert();
	glBindTexture(GL_TEXTURE_2D, texture);
	glAssert();
	// disable 4-byte alignment restrictions
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glAssert();
	// fill w/ empty data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widt, rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
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

		info[i].tx = static_cast<float>(x) / widt;

		// upload data from glyph
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RGBA, GL_UNSIGNED_BYTE, g->bitmap.buffer);
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
	/*forEachChar(str, [&](CharacterInfo& glyph, float x, float y) {
		glm::vec4 rect(glyph.bl, glyph.bt, glyph.bl + glyph.bw, glyph.bt + glyph.bh);
		
		glm::vec2 pos(position.x + x, position.y + y);
		spriteBatch.draw(tex.get(), pos, &rect, color, scale, origin, rotation);
	});*/
	spriteBatch.draw(tex.get(), position, nullptr, color, scale, origin, rotation);
	glAssert();
}

void Font::forEachChar(const std::string& str, FontAction action) {
	float x = 0.f, y = 0.f;

	const char* text = str.c_str();
	for (char c = *text; *text; text++) {
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

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> texCoords;
	std::vector<GLfloat> normals;
	std::vector<GLushort> indices;

	std::string line;
	std::string prefix;
	std::stringstream ss;

	while (!in.eof()) {
		std::getline(in, line);
		ss.str(""); ss.clear();
		ss << line;
		ss >> prefix >> std::ws;
		
		if (prefix == "v") {
			//vertex
			read<GLfloat>(vertices, 3, ss);
		}
		else if (prefix == "vt") {
			// texture coord
			read<GLfloat>(texCoords, 2, ss);
		}
		else if (prefix == "vn") {
			// normal
			read<GLfloat>(normals, 3, ss);
		}
		else if (prefix == "f") {
			// index
			for (size_t i = 0; i < 3; i++) {
				GLushort x, y;
				char c;
				// TODO how about 3 indices?
				ss >> x >> c >> y >> std::ws;
				indices.push_back(x);
				indices.push_back(y);
			}
		}
	}

	// f = v/vt/vn
	for (size_t i = 0; i < indices.size(); i += 3) {
		GLushort vertex = indices[i];
		GLushort texCoord = indices[i + 1];
		this->vertices.push_back(vertices[vertex]); // xyz
		this->vertices.push_back(vertices[vertex + 1]);
		this->vertices.push_back(vertices[vertex + 2]);
		// texcoords
		this->vertices.push_back(texCoords[texCoord]); // uv
		this->vertices.push_back(texCoords[texCoord + 1]);
		// index
		this->indices.push_back(vertex);

	}
	return true;
}