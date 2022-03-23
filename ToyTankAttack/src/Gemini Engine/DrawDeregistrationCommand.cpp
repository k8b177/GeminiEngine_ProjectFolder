#include "DrawDeregistrationCommand.h"

#include "DrawableAttorney.h"

DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable* dr)
	:ptrDr(dr)
{}

void DrawDeregistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneDeregistration(ptrDr);
}