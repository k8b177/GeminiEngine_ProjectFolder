#ifndef KeyboardEventManager_
#define KeyboardEventManager_

#include <map>
#include "Keyboard.h"
#include "Inputable.h"

class SingleKeyEventManager;

class KeyboardEventManager
{

private:
	using MapKeyEntry = std::pair<AZUL_KEY, SingleKeyEventManager*>; // shortcut for map entry
	using MapKeyManager = std::map<AZUL_KEY, SingleKeyEventManager*>; // shortcut for map type
	
	MapKeyManager mapSKMgrs;

public:
	// ---- BIG FOUR ---- //
	KeyboardEventManager() = default;
	KeyboardEventManager(const KeyboardEventManager&) = delete;
	KeyboardEventManager& operator= (const KeyboardEventManager&) = delete;
	~KeyboardEventManager();

	void ProcessKeyEvents();

	void Register(Inputable* in, AZUL_KEY k, EVENT_TYPE e);
	void Deregister(Inputable* in, AZUL_KEY k, EVENT_TYPE e);

	using MapKeyEntryRef = MapKeyManager::iterator; // shortcut for iterator type: map<AZUL_KEY, SingleKeyEventManager*>::iterator

};


#endif KeyboardEventManager_
