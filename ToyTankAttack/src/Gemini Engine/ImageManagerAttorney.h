#ifndef ImageManagerAttorney_
#define ImageManagerAttorney_

#include "ImageManager.h"

class ImageManagerAttorney
{
	// ---- BIG FOUR ---- //
	ImageManagerAttorney() = default;
	ImageManagerAttorney(const ImageManagerAttorney&) = delete;
	ImageManagerAttorney& operator= (const ImageManagerAttorney&) = delete;
	~ImageManagerAttorney() = default;

	friend class Gemini;

private:
	static void Delete() { ImageManager::Delete(); }
};

#endif ImageManagerAttorney_
