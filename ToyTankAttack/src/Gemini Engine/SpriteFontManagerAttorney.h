#ifndef SpriteFontManagerAttorney_
#define SpriteFontManagerAttorney_

#include "SpriteFontManager.h"

class SpriteFontManagerAttorney
{
	// ---- BIG FOUR ---- //
	SpriteFontManagerAttorney() = default;
	SpriteFontManagerAttorney(const SpriteFontManagerAttorney&) = delete;
	SpriteFontManagerAttorney& operator= (const SpriteFontManagerAttorney&) = delete;
	~SpriteFontManagerAttorney() = default;

	friend class Gemini;

private:
	static void Delete() { SpriteFontManager::Delete(); }
};

#endif SpriteFontManagerAttorney_
