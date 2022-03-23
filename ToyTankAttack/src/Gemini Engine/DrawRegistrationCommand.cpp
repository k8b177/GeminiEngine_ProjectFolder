#include "DrawRegistrationCommand.h"

#include "DrawableAttorney.h"

DrawRegistrationCommand::DrawRegistrationCommand(Drawable* dr)
	:ptrDr(dr)
{}

void DrawRegistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneRegistration(ptrDr);
}