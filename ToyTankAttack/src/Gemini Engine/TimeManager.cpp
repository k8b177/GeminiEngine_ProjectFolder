#include "TimeManager.h"

#include "GeminiAttorney.h"

TimeManager* TimeManager::ptrInstance = nullptr;

TimeManager& TimeManager::Instance()
{
	if (!ptrInstance)
		ptrInstance = new TimeManager();
	return *ptrInstance;
}

void TimeManager::privDelete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void TimeManager::privProcessTime()
{
	previousTime = currentTime;
	// currentTime = GeminiAttorney::Time::GetTime();
	currentTime = FrzTime.ComputeGameTime(previousTime);
	frameTime = currentTime - previousTime;
}

float TimeManager::GetTime()
{
	return Instance().currentTime;
}

float TimeManager::GetFrameTime()
{
	return Instance().frameTime;
}