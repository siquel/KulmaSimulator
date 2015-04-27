#include "resources/font.h"
#include "resources/texture.h"
#include <gl/glew.h>
#include "util.h"
#include <algorithm>
#include "GLM.h"
#include "spritebatch.h"

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
		glm::vec4 rect(glyph.tx, texture.get()->height, glyph.bw, glyph.bh);

		glm::vec2 pos(position.x + x, position.y + y);
		// TODO draw to FBO?
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