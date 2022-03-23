#ifndef AlarmRegistrationCommand_
#define AlarmRegistrationCommand_

#include "CommandBase.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmRegistrationCommand : public CommandBase
{
private:
	Alarmable* ptrAl;
	AlarmableManager::ALARM_ID al_id;
	float al_time;

public:
	// ---- BIG FOUR ---- //
	AlarmRegistrationCommand() = delete;
	AlarmRegistrationCommand(const AlarmRegistrationCommand&) = delete;
	AlarmRegistrationCommand& operator= (const AlarmRegistrationCommand&) = delete;
	~AlarmRegistrationCommand() = default;

	AlarmRegistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID id);

	void SetTime(float t); // allows Alarmable to set time that command should pass to AlarmManager


	virtual void Execute() override;
};

#endif AlarmRegistrationCommand_