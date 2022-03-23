#include "KeyRegistrationCommand.h"

#include "InputableAttorney.h"

KeyRegistrationCommand::KeyRegistrationCommand(Inputable* in, AZUL_KEY k, EVENT_TYPE e)
	:ptrIn(in), key(k), e_type(e)
{}

void KeyRegistrationCommand::SetInRef(Inputable::DataMapEntryRef ref)
{
	in_mapEntryRef = ref;
}


void KeyRegistrationCommand::Execute()
{
	InputableAttorney::Registration::KeyRegistration(ptrIn, in_mapEntryRef, key, e_type);
}