#ifndef DrawableManager_
#define DrawableManager_

#include <list>

class Drawable;

class DrawableManager
{

private:
	using StorageList = std::list<Drawable*>;
	StorageList storageList;

public:
	// ---- BIG FOUR ---- //
	DrawableManager() = default;
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator= (const DrawableManager&) = delete;
	~DrawableManager() = default;

	void ProcessElements();

	void Register(Drawable* dr);
	void Deregister(Drawable* dr);

	using StorageListRef = StorageList::iterator; // shortcut for type: list<Drawable*>::iterator
};


#endif DrawableManager_
