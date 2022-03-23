#ifndef ModelManagerAttorney_
#define ModelManagerAttorney_

#include "ModelManager.h"

class ModelManagerAttorney
{
	// ---- BIG FOUR ---- //
	ModelManagerAttorney() = default;
	ModelManagerAttorney(const ModelManagerAttorney&) = delete;
	ModelManagerAttorney& operator= (const ModelManagerAttorney&) = delete;
	~ModelManagerAttorney() = default;

	friend class Gemini;

private:
	static void Delete() { ModelManager::Delete(); }
};

#endif ModelManagerAttorney_
