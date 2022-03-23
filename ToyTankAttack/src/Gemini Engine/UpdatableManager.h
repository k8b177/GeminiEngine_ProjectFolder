#ifndef UpdatableManager_
#define UpdatableManager_

#include <list>

class Updatable;

class UpdatableManager
{

private:
	using StorageList = std::list<Updatable*>;
	StorageList storageList;

public:
	// ---- BIG FOUR ---- //
	UpdatableManager() = default;
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator= (const UpdatableManager&) = delete;
	~UpdatableManager() = default;

	void ProcessElements();

	void Register(Updatable* up);
	void Deregister(Updatable* up);

	using StorageListRef = StorageList::iterator; // shortcut for type: list<Updatable*>::iterator
};


#endif UpdatableManager_
