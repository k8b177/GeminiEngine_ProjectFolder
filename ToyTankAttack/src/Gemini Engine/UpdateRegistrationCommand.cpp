#include "UpdateRegistrationCommand.h"

#include "UpdatableAttorney.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(Updatable* up)
	:ptrUp(up)
{}

void UpdateRegistrationCommand::Execute()
{
	UpdatableAttorney::Registration::SceneRegistration(ptrUp);
}