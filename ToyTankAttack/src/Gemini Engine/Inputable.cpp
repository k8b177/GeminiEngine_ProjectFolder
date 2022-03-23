#include "Inputable.h"

#include "SceneManager.h"
#include "SceneAttorney.h"
#include "KeyRegistrationCommand.h"
#include "KeyDeregistrationCommand.h"


// Constructor for creating new RegistrationData
Inputable::RegistrationData::RegistrationData(Inputable* in, AZUL_KEY k, EVENT_TYPE e)
{
	this->RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED; // set to Deregistered
	this->pRegistrationCmd = new KeyRegistrationCommand(in, k, e); // create the registration command for this inputable with the corresponding key event
	this->pDeregistrationCmd = new KeyDeregistrationCommand(in, k, e); // create the deregistration command
}

// Destructor for RegistrationData
Inputable::RegistrationData::~RegistrationData()
{
	delete this->pRegistrationCmd;
	delete this->pDeregistrationCmd;
}

Inputable::~Inputable()
{
	// deleting all RegistrationData objects in the maps

	// cleaning up key presses
	DataMapEntryRef ref = PressDataMap.begin();
	while (ref != PressDataMap.end())
	{
		delete ref->second;
		ref++;
	}

	// cleaning up key releases
	ref = ReleaseDataMap.begin();
	while (ref != ReleaseDataMap.end())
	{
		delete ref->second;
		ref++;
	}
}


void Inputable::SetDeleteRef(AZUL_KEY k, EVENT_TYPE e, SingleKeyEventManager::InputableCollectionRef sk_ref)
{
	// find the ref in the correct map so we can update the RegData corresponding to the key event for this inputable
	DataMapEntryRef ref;
	if (e == EVENT_TYPE::KEY_PRESS)
	{
		ref = PressDataMap.find(k);
	}
	else
	{
		ref = ReleaseDataMap.find(k);
	}

	// give the RegData for the key event in this map a reference to the iterator in the SKManager
	ref->second->pMyDeleteRef = sk_ref;
}

SingleKeyEventManager::InputableCollectionRef Inputable::GetDeleteRef(AZUL_KEY k, EVENT_TYPE e)
{
	// find the ref in the correct map so we can find the RegData corresponding to the key event for this inputable
	DataMapEntryRef ref;
	if (e == EVENT_TYPE::KEY_PRESS)
	{
		ref = PressDataMap.find(k);
		assert(ref != PressDataMap.end());
	}
	else
	{
		ref = ReleaseDataMap.find(k);
		assert(ref != ReleaseDataMap.end());
	}

	// give back the save delete ref for the SKManager's map
	return ref->second->pMyDeleteRef;
}


void Inputable::SceneRegistration(DataMapEntryRef ref, AZUL_KEY k, EVENT_TYPE e)
{
	// make sure key event is pending registration
	assert(ref->second->RegStateCurr == RegistrationState::PENDING_REGISTRATION);

	// register to scene (adding to keyboard manager's map if necessary and sk managers map)
	SceneAttorney::XAblesAccess::Register(SceneManager::GetCurrentScene(), k, e, this);

	// update current registration state
	ref->second->RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::SceneDeregistration(DataMapEntryRef ref, AZUL_KEY k, EVENT_TYPE e)
{
	// make sure key event is pending deregistration
	assert(ref->second->RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);

	// deregister from scene (removing from sk managers map)
	SceneAttorney::XAblesAccess::Deregister(SceneManager::GetCurrentScene(), k, e, this);

	// update current registration state
	ref->second->RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}


void Inputable::SubmitKeyRegistration(AZUL_KEY k, EVENT_TYPE e)
{
	DataMapEntryRef ref;
	if (e == EVENT_TYPE::KEY_PRESS) // trying to register KEY_PRESS 
	{
		ref = PressDataMap.find(k); // search the press map for k and save the ref to the DataMapEntry
		if (ref == PressDataMap.end())
		{
			// if it's not in the map, we need to insert it
			ref = PressDataMap.insert(DataMapEntry(k, new RegistrationData(this, k, EVENT_TYPE::KEY_PRESS))).first; // save the ref to the DataMapEntry
			// give the commands the iterator so they can access the RegData without another map search
			ref->second->pRegistrationCmd->SetInRef(ref);
			ref->second->pDeregistrationCmd->SetInRef(ref);
		}
	}
	else // trying to register KEY_RELEASE
	{
		ref = ReleaseDataMap.find(k); // search the release map for k and save the ref to the DataMapEntry
		if (ref == ReleaseDataMap.end())
		{
			// if it's not in the map, we need to insert it
			ref = ReleaseDataMap.insert(DataMapEntry(k, new RegistrationData(this, k, EVENT_TYPE::KEY_RELEASE))).first; // save the ref to the DataMapEntry
			// give the commands the iterator so they can access the RegData without another map search
			ref->second->pRegistrationCmd->SetInRef(ref);
			ref->second->pDeregistrationCmd->SetInRef(ref);
		}
	}

	// make sure key event is CURRENTLY_DEREGISTERED
	assert(ref->second->RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);

	// submit registration command for this key event
	SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), ref->second->pRegistrationCmd); // put the command in the broker's stack

	// update current registration state of this key event
	ref->second->RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}


void Inputable::SubmitKeyDeregistration(AZUL_KEY k, EVENT_TYPE e)
{
	DataMapEntryRef ref;
	if (e == EVENT_TYPE::KEY_PRESS) // trying to deregister KEY_PRESS 
	{
		ref = PressDataMap.find(k); // search the press map for k and save the ref to the DataMapEntry
		assert(ref != PressDataMap.end()); // makes sure k has actually been added to the press map
	}
	else // trying to register KEY_RELEASE
	{
		ref = ReleaseDataMap.find(k); // search the release map for k and save the ref to the DataMapEntry
		assert(ref != ReleaseDataMap.end()); // makes sure k has actually been added to the release map
	}

	// make sure registration status is CURRENTLY_REGISTERED
	assert(ref->second->RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);

	// submit deregistration command for this key event
	SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), ref->second->pDeregistrationCmd); // put the command in the broker's stack

	// update current registration state of this key event
	ref->second->RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

