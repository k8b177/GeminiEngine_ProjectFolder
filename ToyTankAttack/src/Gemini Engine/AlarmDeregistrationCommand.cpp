#include "AlarmDeregistrationCommand.h"

#include "AlarmableAttorney.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID id)
	:ptrAl(al), al_id(id)
{}

void AlarmDeregistrationCommand::Execute()
{
	AlarmableAttorney::Registration::AlarmDeregistration(ptrAl, al_id);
}