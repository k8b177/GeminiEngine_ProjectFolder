#include "SingleKeyEventManager.h"

#include "InputableAttorney.h"

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY k)
	:myKey(k), prevFrameState(KeyState::UP)
{}

void SingleKeyEventManager::Register(Inputable* in, EVENT_TYPE e)
{ 
	InputableCollectionRef ref;
	if (e == EVENT_TYPE::KEY_PRESS) // if registering for press, add inputable to press list
	{
		ref = keyPressCol.insert(keyPressCol.end(), in);
	}
	else // if registering for release, add inputable to relase list
	{
		ref = keyReleaseCol.insert(keyReleaseCol.end(), in);
	}

	// set the delete ref
	InputableAttorney::Manager::SetDeleteRef(in, myKey, e, ref);
}

void SingleKeyEventManager::Deregister(Inputable* in, EVENT_TYPE e)
{
	// get the saved reference to the inputables place in the map
	InputableCollectionRef ref = InputableAttorney::Manager::GetDeleteRef(myKey, e, in);

	// erase from the correct map (press or release)
	if (e == EVENT_TYPE::KEY_PRESS)
	{
		keyPressCol.erase(ref);
	}
	else
	{
		keyReleaseCol.erase(ref);
	}
}

void SingleKeyEventManager::ProcessKeyEvent()
{
	bool isDown = Keyboard::GetKeyState(myKey);

	if (isDown)
	{
		// if key is down, check if it was up last frame
		if (prevFrameState == KeyState::UP)
		{
			// call KeyPress on all the Inputables registered to watch for it
			DistributeKeyPressCall();

			// update the prevFrameState
			prevFrameState = KeyState::DOWN;
		}
	}
	else
	{
		// if key is up, check if it was down last frame
		if (prevFrameState == KeyState::DOWN)
		{
			// call KeyRelease on all the Inputables registered to watch for it
			DistributeKeyReleaseCall();

			// update the prevFrameState
			prevFrameState = KeyState::UP;
		}
	}
}

void SingleKeyEventManager::DistributeKeyPressCall()
{
	for (Inputable* in : keyPressCol)
	{
		InputableAttorney::Manager::KeyPressed(in, myKey);
	}
}

void SingleKeyEventManager::DistributeKeyReleaseCall()
{
	for (Inputable* in : keyReleaseCol)
	{
		InputableAttorney::Manager::KeyReleased(in, myKey);
	}
}