#include "UpdatableManager.h"

#include "UpdatableAttorney.h"

void UpdatableManager::Register(Updatable* up)
{
	// inserting "up" into storageList and getting the iterator
	StorageListRef ref = storageList.insert(storageList.end(), up);

	// sending the iterator reference to "up" object for fast delete later
	UpdatableAttorney::Manager::SetDeleteRef(up, ref);
}

void UpdatableManager::Deregister(Updatable* up)
{
	// erase up from storagelist
	storageList.erase(UpdatableAttorney::Manager::GetDeleteRef(up)); // using saved reference to iterator
																	 // no linear search needed --> constant time
}

void UpdatableManager::ProcessElements()
{
	for (Updatable* up : storageList)
	{
		UpdatableAttorney::Manager::Update(up);
	}
}