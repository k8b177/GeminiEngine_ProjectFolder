#ifndef SingleKeyEventManager_
#define SingleKeyEventManager_

#include "Keyboard.h"
#include "EVENT_TYPEEnum.h"
#include <list>

class Inputable;

class SingleKeyEventManager
{
private:
	AZUL_KEY myKey;

	enum class KeyState { DOWN, UP };
	KeyState prevFrameState; // holds state of key on previous frame

	//using InputableCollection = std::list<Inputable*>; // shortcut for list of Inputables
	using InputableCollection = std::list<Inputable*>;

	InputableCollection keyPressCol; // list of Inputables that have requested to watch for key presses for this key
	InputableCollection keyReleaseCol; // list of Inputables that have requested to watch for key releases for this key

	void DistributeKeyPressCall();
	void DistributeKeyReleaseCall();

public:
	// ---- BIG FOUR ---- //
	SingleKeyEventManager() = delete;
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager& operator= (const SingleKeyEventManager&) = delete;
	~SingleKeyEventManager() = default;

	SingleKeyEventManager(AZUL_KEY k);

	
	void ProcessKeyEvent(); // processes the one key this manager is assigned

	void Register(Inputable* in, EVENT_TYPE e);
	void Deregister(Inputable* in, EVENT_TYPE e);
	
	using InputableCollectionRef = InputableCollection::iterator; // shortcut for std::list<Inputable*>::iterator
};


#endif SingleKeyEventManager_
