#include "AlarmRegistrationCommand.h"

#include "AlarmableAttorney.h"

AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID id)
	:ptrAl(al), al_id(id), al_time(0.0f)
{}

void AlarmRegistrationCommand::SetTime(float t)
{
	this->al_time = t;
}

void AlarmRegistrationCommand::Execute()
{
	AlarmableAttorney::Registration::AlarmRegistration(ptrAl, al_time, al_id);
}