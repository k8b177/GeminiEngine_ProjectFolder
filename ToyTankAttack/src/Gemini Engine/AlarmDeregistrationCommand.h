#ifndef AlarmDeregistrationCommand_
#define AlarmDeregistrationCommand_

#include "CommandBase.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmDeregistrationCommand : public CommandBase
{
private:
	Alarmable* ptrAl;
	AlarmableManager::ALARM_ID al_id;

public:
	// ---- BIG FOUR ---- //
	AlarmDeregistrationCommand() = delete;
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand&) = delete;
	AlarmDeregistrationCommand& operator= (const AlarmDeregistrationCommand&) = delete;
	~AlarmDeregistrationCommand() = default;

	AlarmDeregistrationCommand(Alarmable* ptrAl, AlarmableManager::ALARM_ID al_id);

	virtual void Execute() override;
};

#endif AlarmDeregistrationCommand_