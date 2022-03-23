#include "KeyboardEventManager.h"

#include "SingleKeyEventManager.h"

void KeyboardEventManager::Register(Inputable* in, AZUL_KEY k, EVENT_TYPE e)
{
	MapKeyEntryRef ref;

	// search the SKManager map for key k
	ref = mapSKMgrs.find(k);

	if (ref == mapSKMgrs.end()) // if there is not a SKManager for key k, create one
	{
		ref = mapSKMgrs.insert(MapKeyEntry(k, new SingleKeyEventManager(k))).first;
	}

	// register the inputable to watch for either PRESS or RELEASE event in the SKManager for key k
	ref->second->Register(in, e);
}

void KeyboardEventManager::Deregister(Inputable* in, AZUL_KEY k, EVENT_TYPE e)
{
	MapKeyEntryRef ref;

	// search the SKManager map for key k
	ref = mapSKMgrs.find(k);
	assert(ref != mapSKMgrs.end()); // make sure there is an SKManager for key k in the map

	// deregister the inputable from either PRESS or RELEASE event in the SKManager for key k
	ref->second->Deregister(in, e);
}

void KeyboardEventManager::ProcessKeyEvents()
{
	MapKeyEntryRef ref = mapSKMgrs.begin(); // get first entry

	// loop through all SingleKeyEventManagers
	while (ref != mapSKMgrs.end())
	{
		// call ProcessKeyEvent() for every SingleKeyEventManager in the map
		ref->second->ProcessKeyEvent();
		ref++;
	}
}

KeyboardEventManager::~KeyboardEventManager()
{
	MapKeyEntryRef ref = mapSKMgrs.begin(); // get first entry of SingleKeyEventManagers map

	// loop through all SingleKeyEventManagers and delete them
	while (ref != mapSKMgrs.end())
	{
		delete ref->second;
		ref++;
	}
}