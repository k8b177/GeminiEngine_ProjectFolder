#ifndef TimeManager_
#define TimeManager_

#include "FreezeTime.h"

class TimeManager
{
	friend class TimeManagerAttorney;

private:
	static TimeManager* ptrInstance;

	static TimeManager& Instance();

	// ---- BIG FOUR ---- //
	TimeManager() = default;
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator= (const TimeManager&) = delete;
	~TimeManager() = default;

	// ---- PRIVATE METHODS ---- //
	void privDelete();
	void privProcessTime();


	// ---- PRIVATE STATIC METHODS (accessed through attorney) ----//
	static void Delete() { Instance().privDelete(); } // No User acces, only Attorney
	static void ProcessTime() { Instance().privProcessTime(); } // No User access, only Attorney

	// ---- PRIVATE MEMBER VARS ---- //
	float currentTime = 0.0f;
	float frameTime = 0.0f;
	float previousTime = 0.0f;

	FreezeTime FrzTime;


public:
	static float GetTime();
	static float GetFrameTime();
};

#endif TimeManager_