#include "UpdateDeregistrationCommand.h"

#include "UpdatableAttorney.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(Updatable* up)
	:ptrUp(up)
{}

void UpdateDeregistrationCommand::Execute()
{
	UpdatableAttorney::Registration::SceneDeregistration(ptrUp);
}