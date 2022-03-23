#include "CollisionManager.h"

#include "CollidableGroup.h"

CollisionManager::GemTypeID CollisionManager::TypeIDNextNumber = 0;

CollisionManager::CollisionManager()
{
	// initialize all the CollidableGroups in the Collection to nullptr
	for (int ind = 0; ind < MAX_COLLISION_GROUP; ind++)
	{
		ColGroupCollection.push_back(nullptr);
	}
}

CollisionManager::~CollisionManager()
{
	// delete all the Collidable Groups
	for (CollidableGroup* cg : ColGroupCollection)
		delete cg;

	// delete all the Collision Test Commands
	for (CollisionTestCommandBase* c : colTestCommands)
		delete c;
}

void CollisionManager::SetGroupForTypeID(CollisionManager::GemTypeID ind)
{
	// if collision group does not exist for the type, create it
	if (ColGroupCollection[ind] == nullptr)
		ColGroupCollection[ind] = new CollidableGroup();
}

CollidableGroup* CollisionManager::GetColGroup(GemTypeID id)
{
	return ColGroupCollection[id];
}

void CollisionManager::ProcessCollisions()
{
	// loop through CollisionTestCommands and Execute them
	for (CollisionTestCommands::iterator it = colTestCommands.begin(); it != colTestCommands.end(); it++)
	{
		(*it)->Execute();
	}
}