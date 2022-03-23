#include "CollisionDeregistrationCommand.h"

#include "CollidableAttorney.h"

CollisionDeregistrationCommand::CollisionDeregistrationCommand(Collidable* col)
	:ptrCol(col)
{}

void CollisionDeregistrationCommand::Execute()
{
	CollidableAttorney::Registration::SceneDeregistration(ptrCol);
}