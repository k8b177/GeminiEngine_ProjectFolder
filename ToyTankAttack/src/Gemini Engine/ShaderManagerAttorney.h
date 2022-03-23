#ifndef ShaderManagerAttorney_
#define ShaderManagerAttorney_

#include "ShaderManager.h"

class ShaderManagerAttorney
{
	// ---- BIG FOUR ---- //
	ShaderManagerAttorney() = default;
	ShaderManagerAttorney(const ShaderManagerAttorney&) = delete;
	ShaderManagerAttorney& operator= (const ShaderManagerAttorney&) = delete;
	~ShaderManagerAttorney() = default;

	friend class Gemini;

private:
	static void Delete() { ShaderManager::Delete(); }
};

#endif ShaderManagerAttorney_
