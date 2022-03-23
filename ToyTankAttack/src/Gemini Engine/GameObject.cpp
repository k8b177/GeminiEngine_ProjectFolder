#include "GameObject.h"

#include "GameObjectEntryCommand.h"
#include "GameObjectExitCommand.h"
#include "SceneAttorney.h"
#include "SceneManager.h"

GameObject::GameObject()
	:currState(RegistrationState::CURRENTLY_DEREGISTERED)
{
	pRegCmd = new GameObjectEntryCommand(this);
	pDeregCmd = new GameObjectExitCommand(this);
}

GameObject::~GameObject()
{
	delete pRegCmd;
	delete pDeregCmd;
}

void GameObject::SubmitEntry()
{
	// make sure *this* is already deregistered
	assert(currState == RegistrationState::CURRENTLY_DEREGISTERED);

	// submit registration command
	SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), pRegCmd);

	// update current registration state
	currState = RegistrationState::PENDING_REGISTRATION;
}

void GameObject::SubmitExit()
{
	if (currState == RegistrationState::PENDING_DEREGISTRATION)
	{
		// do nothing
		// game object has already been asked to be removed - don't submit another command
	}
	else
	{
		// make sure *this* is already registered
		assert(currState == RegistrationState::CURRENTLY_REGISTERED);

		// submit deregistration command
		SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), pDeregCmd);

		// update current registration state
		currState = RegistrationState::PENDING_DEREGISTRATION;
	}
}

void GameObject::ConnectToScene()
{
	// make sure *this* is pending registration
	assert(currState == RegistrationState::PENDING_REGISTRATION);

	// update current registration state
	currState = RegistrationState::CURRENTLY_REGISTERED;

	// call user's SceneEntry to connect to scene
	this->SceneEntry();
}

void GameObject::DisconnectFromScene()
{
	// make sure *this* is pending deregistration
	assert(currState == RegistrationState::PENDING_DEREGISTRATION);

	// call user's SceneExit to disconnect from scene
	this->SceneExit();

	// update current registration state
	currState = RegistrationState::CURRENTLY_DEREGISTERED;
}