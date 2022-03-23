#include "Alarmable.h"

#include "SceneManager.h"
#include "SceneAttorney.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"

Alarmable::Alarmable()
{
	// looping through RegData and setting up initial data for all the alarms for this alarmable
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++)
	{
		// setting registration state
		RegData[i].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

		// creating instances of registration and deregistration commands and saving references
		RegData[i].pRegistrationCmd = new AlarmRegistrationCommand(this, (AlarmableManager::ALARM_ID)i);
		RegData[i].pDeregistrationCmd = new AlarmDeregistrationCommand(this, (AlarmableManager::ALARM_ID)i);
	}
}

Alarmable::~Alarmable()
{
	// deleting instances of registration and deregistration commands for every alarm for this alarmable
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++)
	{
		delete RegData[i].pRegistrationCmd;
		delete RegData[i].pDeregistrationCmd;
	};
}

void Alarmable::SetDeleteRef(AlarmableManager::ALARM_ID id, AlarmableManager::TimeLineEntryRef ref)
{
	// get the index for the alarm we want to submit (alarm #id)
	int index = (int)id;

	// set the delete ref for that alarm
	RegData[index].pMyDeleteRef = ref;
}

AlarmableManager::TimeLineEntryRef Alarmable::GetDeleteRef(AlarmableManager::ALARM_ID id)
{
	// get the index for the alarm we want to submit (alarm #id)
	int index = (int)id;

	// return the reference to the iterator of that alarm in the timeline
	return RegData[index].pMyDeleteRef;
}

void Alarmable::AlarmRegistration(float t, AlarmableManager::ALARM_ID id)
{
	// get the index for the alarm we want to submit (alarm #id)
	int index = (int)id;

	// make sure *this* is pending registration
	assert(RegData[index].RegStateCurr == RegistrationState::PENDING_REGISTRATION);

	// register to scene (adding to updatable manager's storage list)
	SceneAttorney::XAblesAccess::Register(SceneManager::GetCurrentScene(), t, id, this);

	// update current registration state
	RegData[index].RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::AlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	// get the index for the alarm we want to submit (alarm #id)
	int index = (int)id;

	// make sure this alarm is pending deregistration
	assert(RegData[index].RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);

	// deregister from scene (removing from alarmable manager's timeline)
	SceneAttorney::XAblesAccess::Deregister(SceneManager::GetCurrentScene(), id, this);

	// update current registration state
	RegData[index].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Alarmable::SubmitAlarmRegistration(float t, AlarmableManager::ALARM_ID id)
{
	// get the index for the alarm we want to submit (alarm #id)
	int index = (int)id;

	// make sure *this* is already deregistered
	assert(RegData[index].RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);

	// submit registration command
	RegData[index].pRegistrationCmd->SetTime(t); // give the command the time specified by the user
	SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), RegData[index].pRegistrationCmd); // put the command in the broker's stack

	// update current registration state
	RegData[index].RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	// get the index for the alarm we want to submit (alarm #id)
	int index = (int)id;

	// make sure the alarm is already registered
	assert(RegData[index].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);

	// submit deregistration command
	SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), RegData[index].pDeregistrationCmd);

	// update current registration state
	RegData[index].RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}


void Alarmable::TriggerAlarm(AlarmableManager::ALARM_ID id)
{
	// get the index for the alarm we want to trigger (alarm #id)
	int index = (int)id;

	// Set registration state to DEREGISTERED first to allow alarm to be reset in the event itself
	RegData[index].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

	// Trigger the right Alarm based on the id
	switch (id)
	{
	case AlarmableManager::ALARM_ID::ALARM_0:
		this->Alarm0();
		break;
	case AlarmableManager::ALARM_ID::ALARM_1:
		this->Alarm1();
		break;
	case AlarmableManager::ALARM_ID::ALARM_2:
		this->Alarm2();
		break;
	}
}

float Alarmable::GetAlarmTime(AlarmableManager::ALARM_ID id)
{
	// get the index for the alarm we want to check (alarm #id)
	int index = (int)id;

	// make sure the alarm is already registered
	assert(RegData[index].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);

	// return the alarm time
	return SceneAttorney::XAblesAccess::GetAlarmableMgr()->GetAlarmTime(id, this);
}

void Alarmable::SetAlarmTime(float timeOffset, AlarmableManager::ALARM_ID id)
{
	// get the index for the alarm we want to check (alarm #id)
	int index = (int)id;

	// make sure the alarm is already registered
	assert(RegData[index].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);

	// set the new alarm time
	SceneAttorney::XAblesAccess::GetAlarmableMgr()->SetAlarmTime(timeOffset, id, this);
}