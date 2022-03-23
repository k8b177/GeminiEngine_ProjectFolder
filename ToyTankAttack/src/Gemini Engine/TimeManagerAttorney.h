#ifndef TimeManagerAttorney_
#define TimeManagerAttorney_

#include "TimeManager.h"

class TimeManagerAttorney
{
	// ---- BIG FOUR ---- //
	TimeManagerAttorney() = default;
	TimeManagerAttorney(const TimeManagerAttorney&) = delete;
	TimeManagerAttorney& operator= (const TimeManagerAttorney&) = delete;
	~TimeManagerAttorney() = default;

	friend class Gemini;

private:
	static void ProcessTime() { TimeManager::ProcessTime(); }
	static void Delete() { TimeManager::Delete(); }
};

#endif TimeManagerAttorney_
