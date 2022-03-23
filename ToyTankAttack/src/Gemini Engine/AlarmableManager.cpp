#include "AlarmableManager.h"

#include "AlarmableAttorney.h"
#include "TimeManager.h"


void AlarmableManager::Register(float t, AlarmableManager::ALARM_ID id, Alarmable* al)
{
	// calculating absolute time when alarm should trigger (add offset to current time)
	float absoluteTime = TimeManager::GetTime() + t; 

	// inserting Alarmable/ALARM_ID pair into timeline with absolute time and getting the iterator
	TimeLineEntryRef ref = timeline.insert(TimeLineEntry(absoluteTime, AlarmEvent(al, id)));

	// sending the iterator reference to "al" object (with the alarm id) for fast delete later
	AlarmableAttorney::Manager::SetDeleteRef(al, id, ref);
}

void AlarmableManager::Deregister(AlarmableManager::ALARM_ID id, Alarmable* al)
{
	// erase up from timeline
	timeline.erase(AlarmableAttorney::Manager::GetDeleteRef(id, al)); // using saved reference to iterator
																	  // no linear search needed --> constant time
}

float AlarmableManager::GetAlarmTime(AlarmableManager::ALARM_ID id, Alarmable* al)
{
	// get the iterator to the timeline entry
	TimeLineEntryRef ref = AlarmableAttorney::Manager::GetDeleteRef(id, al);

	// get the gameClock time 
	float gameClockTime = TimeManager::GetTime();

	// time left on alarm is  absolute time of entry minus gameClock time
	return ref->first - gameClockTime;
}

void AlarmableManager::SetAlarmTime(float timeOffset, AlarmableManager::ALARM_ID id, Alarmable* al)
{
	// getting timeline entry
	TimeLineEntryRef ref = AlarmableAttorney::Manager::GetDeleteRef(id, al);
	// getting timeline etry's absolute time
	float originalTime = ref->first;

	// delete ref from timeline
	timeline.erase(ref);

	// calculating the new time
	float newAbsoluteTime = originalTime + timeOffset;

	// check newAbsoluteTime is in the future
	assert(newAbsoluteTime > TimeManager::GetTime());

	// inserting Alarmable/ALARM_ID pair into timeline with absolute time and getting the iterator
	ref = timeline.insert(TimeLineEntry(newAbsoluteTime, AlarmEvent(al, id)));

	// sending the iterator reference to "al" object (with the alarm id) for fast delete later
	AlarmableAttorney::Manager::SetDeleteRef(al, id, ref);
}

void AlarmableManager::ProcessAlarms()
{
	TimeLineEntryRef ref = timeline.begin();
	AlarmEvent alEvent;

	// Trigger all alarms whose absolute time passed during the last frame
	float currentTime = TimeManager::GetTime();
	while (ref != timeline.end() && ref->first <= currentTime)
	{
		alEvent = ref->second; // get the AlarmEvent whose time has passed
		AlarmableAttorney::Manager::TriggerAlarm(alEvent); // trigger the alarm#id of the alarmable
		timeline.erase(ref); // remove entry from timeline (it's been triggered)
		ref = timeline.begin(); // reset to first timeline entry
	}
}