#include "CollisionRegistrationCommand.h"

#include "CollidableAttorney.h"

CollisionRegistrationCommand::CollisionRegistrationCommand(Collidable* col)
	:ptrCol(col)
{}

void CollisionRegistrationCommand::Execute()
{
	CollidableAttorney::Registration::SceneRegistration(ptrCol);
}