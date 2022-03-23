#ifndef ScreenLogAttorney_
#define ScreenLogAttorney_

#include "ScreenLog.h"

class ScreenLogAttorney
{
	// ---- BIG FOUR ---- //
	ScreenLogAttorney() = default;
	ScreenLogAttorney(const ScreenLogAttorney&) = delete;
	ScreenLogAttorney& operator= (const ScreenLogAttorney&) = delete;
	~ScreenLogAttorney() = default;

	friend class Gemini;

private:
	static void Delete() { ScreenLog::Delete(); }
	static void Render() { ScreenLog::Render(); }
};

#endif ScreenLogAttorney_
