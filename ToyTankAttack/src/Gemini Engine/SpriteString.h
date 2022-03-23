
#ifndef _SpriteString
#define _SpriteString

#include <list>

class GeminiSprite;
class SpriteFont;

class SpriteString
{
public:
	using Glyph = GeminiSprite;
	using GlyphCollection = std::list<Glyph*>;

private:
	float posx;
	float posy;
	float height;
	float width;

	GlyphCollection glyphs;

	SpriteFont* sfont;

public:
	SpriteString() = default;
	~SpriteString() = default;
	SpriteString(const SpriteString&) = delete;
	SpriteString& operator=(const SpriteString&) = delete;

	SpriteString(SpriteFont* sf, std::string s, float x, float y);

	float GetWidth();
	float GetHeight();
	float GetPosX();
	float GetPosY();
	void Set(float x, float y);
	void Set(SpriteFont* sf, std::string s, float x, float y);
	void SetString(std::string s);

	void Render();

};

#endif _SpriteString