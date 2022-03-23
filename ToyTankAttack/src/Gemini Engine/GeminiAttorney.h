#ifndef GeminiAttorney_
#define GeminiAttorney_

#include "Gemini.h"

class GeminiAttorney
{
	// ---- BIG FOUR ---- //
	GeminiAttorney() = default;
	GeminiAttorney(const GeminiAttorney&) = delete;
	GeminiAttorney& operator= (const GeminiAttorney&) = delete;
	~GeminiAttorney() = default;

public:
	// methods in Gemini only available to TimeManager and FreezeTime
	class Time
	{
	private:
		friend class TimeManager;
		friend class FreezeTime;

		static float GetTime() { return Gemini::GetTime(); } // returns system clock time
	};
};

#endif GeminiAttorney_
