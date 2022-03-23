#include "CollidableGroup.h"

#include "CollidableAttorney.h"

const CollidableGroup::CollidableCollection& CollidableGroup::GetColliderCollection()
{
	return CollideCol;
}

void CollidableGroup::Register(Collidable* c, CollidableCollectionRef& ref)
{
	// inserting "c" into CollideCol and setting the iterator
	ref = CollideCol.insert(CollideCol.end(), c);
}

void CollidableGroup::Deregister(const CollidableCollectionRef& ref)
{
	// erase up from storagelist
	CollideCol.erase(ref);	// using saved reference to iterator
							// no linear search needed --> constant time
}