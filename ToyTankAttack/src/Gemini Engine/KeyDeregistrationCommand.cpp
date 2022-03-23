#include "KeyDeregistrationCommand.h"

#include "InputableAttorney.h"

KeyDeregistrationCommand::KeyDeregistrationCommand(Inputable* in, AZUL_KEY k, EVENT_TYPE e)
	:ptrIn(in), key(k), e_type(e)
{}

void KeyDeregistrationCommand::SetInRef(Inputable::DataMapEntryRef ref)
{
	in_mapEntryRef = ref;
}

void KeyDeregistrationCommand::Execute()
{
	InputableAttorney::Registration::KeyDeregistration(ptrIn, in_mapEntryRef, key, e_type);
}