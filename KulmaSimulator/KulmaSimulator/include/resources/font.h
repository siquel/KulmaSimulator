#ifndef FONT_H
#define FONT_H
#include <functional>
#include "resource.h"
#include <memory>
class SpriteBatch;
class Texture;
#include "GLM.h"
#include <ft2build.h>
#include FT_FREETYPE_H
struct CharacterInfo {
	float ax; // advance.x
	float ay; // advance.y

	float bw; // bitmap.width;
	float bh; // bitmap.rows;

	float bl; // bitmap_left;
	float bt; // bitmap_top;

	float tx; // x offset of glyph in texture coordinates
};
typedef std::function<void(CharacterInfo&, float, float)> FontAction;
class Font : public Resource {
private:
	CharacterInfo info[128];
	float spacing;
	std::unique_ptr<Texture> texture;
	void forEachChar(const std::string& str, FontAction action);
public:
	bool readFromFile(const std::string& path);
	void drawString(SpriteBatch& spriteBatch, std::string& str, glm::vec2& position, glm::vec4& color, float rotation, glm::vec2& origin, glm::vec2& scale);

	Font();
	~Font();
};
#endif