#ifndef GodCamControllerAttorney_
#define GodCamControllerAttorney_

#include "GodCamController.h"

class GodCamControllerAttorney
{
	// ---- BIG FOUR ---- //
	GodCamControllerAttorney() = default;
	GodCamControllerAttorney(const GodCamControllerAttorney&) = delete;
	GodCamControllerAttorney& operator= (const GodCamControllerAttorney&) = delete;
	~GodCamControllerAttorney() = default;

	friend class Gemini;

private:
	static void Delete() { GodCamController::Delete(); }
};

#endif GodCamControllerAttorney_
