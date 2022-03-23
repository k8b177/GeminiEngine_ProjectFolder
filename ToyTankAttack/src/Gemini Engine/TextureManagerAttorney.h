#ifndef TextureManagerAttorney_
#define TextureManagerAttorney_

#include "TextureManager.h"

class TextureManagerAttorney
{
	// ---- BIG FOUR ---- //
	TextureManagerAttorney() = default;
	TextureManagerAttorney(const TextureManagerAttorney&) = delete;
	TextureManagerAttorney& operator= (const TextureManagerAttorney&) = delete;
	~TextureManagerAttorney() = default;

	friend class Gemini;

private:
	static void Delete() { TextureManager::Delete(); }

public:
	class SpriteFontAccess
	{
		friend class SpriteFont;
	private:
		static void LoadSpriteFontTexture(const std::string& key, const std::string& fontpath) { TextureManager::LoadSpriteFontTexture(key, fontpath); }
	};
};

#endif TextureManagerAttorney_
