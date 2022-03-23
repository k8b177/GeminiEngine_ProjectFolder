#ifndef AlarmableManager_
#define AlarmableManager_

#include <map>

class Alarmable;

class AlarmableManager
{

public:

	///-------------------------------------------------------------------------------------------------
	/// \enum	ALARM_ID
	///
	/// \brief	Values that represent Alarm identifiers
	/// 		
	/// Use to specify a particular \b Alarm when Registering or Deregistering.
	/// 
	/// \par Example:
	///	\code
	///  Frigate::Frigate()
	///	{
	///		// Alarm0 will be called 5 seconds after the Frigate is created
	///		Alarmable::SubmitAlarmRegistration(5.0f, AlarmableManager::ALARM_ID::ALARM_0);
	///	}
	///	\endcode
	/// 		
	///-------------------------------------------------------------------------------------------------
	enum class ALARM_ID { ALARM_0, ALARM_1, ALARM_2}; // enum for alarm number
	

	/// \cond
	static const int ALARM_NUMBER = 3;

	// ---- BIG FOUR ---- //
	AlarmableManager() = default;
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator= (const AlarmableManager&) = delete;
	~AlarmableManager() = default;


	void ProcessAlarms(); // called every frame, checks timeline for alarms that have passed in the last frame and triggers them
	void Register(float t, AlarmableManager::ALARM_ID id, Alarmable* up); // adds specified Alarmable to timeline (sorted by absolute time)
	void Deregister(AlarmableManager::ALARM_ID id, Alarmable* al); // removes specified Alarmable from timeline

	using AlarmEvent = std::pair<Alarmable*, ALARM_ID>;

	float GetAlarmTime(AlarmableManager::ALARM_ID, Alarmable* al);
	void SetAlarmTime(float timeOffset, AlarmableManager::ALARM_ID, Alarmable* al);

private:
	using TimeLineEntry = std::pair<float, AlarmEvent>;
	using TimeLineMap = std::multimap<float, AlarmEvent>;
	TimeLineMap timeline; // absolute times mapped to Alarmable/ALARM_ID pairs

public:
	using TimeLineEntryRef = TimeLineMap::iterator; // shortcut for type: multimap<float, Alarmable*>::iterator
	/// \endcond
};


#endif AlarmableManager_
