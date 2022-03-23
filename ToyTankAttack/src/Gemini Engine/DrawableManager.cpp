#include "DrawableManager.h"

#include "DrawableAttorney.h"

void DrawableManager::Register(Drawable* dr)
{
	// inserting "dr" into storageList and getting the iterator
	StorageListRef ref = storageList.insert(storageList.end(), dr);

	// sending the iterator reference to "dr" object for fast delete later
	DrawableAttorney::Manager::SetDeleteRef(dr, ref);
}

void DrawableManager::Deregister(Drawable* dr)
{
	// erase up from storagelist
	storageList.erase(DrawableAttorney::Manager::GetDeleteRef(dr)); // using saved reference to iterator
																	 // no linear search needed --> constant time
}

void DrawableManager::ProcessElements()
{
	// Draw all 3D first
	for (Drawable* dr : storageList)
	{
		DrawableAttorney::Manager::Draw(dr);
	}

	// Draw 2D after
	for (Drawable* dr : storageList)
	{
		DrawableAttorney::Manager::Draw2D(dr);
	}
}