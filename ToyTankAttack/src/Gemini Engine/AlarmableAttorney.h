#ifndef AlarmableAttorney_
#define AlarmableAttorney_

#include "Alarmable.h"

class AlarmableAttorney
{
	// ---- BIG FOUR ---- //
	AlarmableAttorney() = default;
	AlarmableAttorney(const AlarmableAttorney&) = delete;
	AlarmableAttorney& operator= (const AlarmableAttorney&) = delete;
	~AlarmableAttorney() = default;

public:
	// methods in Alarmable only available to AlarmableManager
	class Manager
	{
	private:
		friend class AlarmableManager;
		static void TriggerAlarm(AlarmableManager::AlarmEvent alEvent) { alEvent.first->TriggerAlarm(alEvent.second); };
		static void SetDeleteRef(Alarmable* p, AlarmableManager::ALARM_ID id, AlarmableManager::TimeLineEntryRef ref) { p->SetDeleteRef(id, ref); }
		static AlarmableManager::TimeLineEntryRef GetDeleteRef(AlarmableManager::ALARM_ID id, Alarmable* p) { return p->GetDeleteRef(id); }
	};

public:
	// methods in Alarmable only available to AlarmRegistrationCommand and AlarmDeregistrationCommand
	class Registration
	{
		friend class AlarmRegistrationCommand;
		friend class AlarmDeregistrationCommand;
	private:
		static void AlarmRegistration(Alarmable* p, float t, AlarmableManager::ALARM_ID id) { p->AlarmRegistration(t, id); }
		static void AlarmDeregistration(Alarmable* p, AlarmableManager::ALARM_ID id) { p->AlarmDeregistration(id); }
	};
};

#endif AlarmableAttorney_
