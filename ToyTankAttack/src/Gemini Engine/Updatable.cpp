#include "Updatable.h"

#include "SceneManager.h"
#include "SceneAttorney.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"

Updatable::Updatable()
	:RegStateCurr(RegistrationState::CURRENTLY_DEREGISTERED)
{
	// creating instances of registration and deregistration commands and saving references
	pRegistrationCmd = new UpdateRegistrationCommand(this);
	pDeregistrationCmd = new UpdateDeregistrationCommand(this);
}

Updatable::~Updatable()
{
	// deleting instances of registration and deregistration commands
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
}

void Updatable::SetDeleteRef(UpdatableManager::StorageListRef ref)
{
	this->pMyDeleteRef = ref;
}

UpdatableManager::StorageListRef Updatable::GetDeleteRef()
{
	return this->pMyDeleteRef;
}

void Updatable::SceneRegistration()
{
	// make sure *this* is pending registration
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);

	// register to scene (adding to updatable manager's storage list)
	SceneAttorney::XAblesAccess::Register(SceneManager::GetCurrentScene(), this);

	// update current registration state
	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Updatable::SceneDeregistration()
{
	// make sure *this* is pending deregistration
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);

	// deregister from scene (removing from updatable manager's storage list)
	SceneAttorney::XAblesAccess::Deregister(SceneManager::GetCurrentScene(), this);

	// update current registration state
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Updatable::SubmitUpdateRegistration()
{
	// make sure *this* is already deregistered
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED); 

	// submit registration command
	SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), pRegistrationCmd);

	// update current registration state
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Updatable::SubmitUpdateDeregistration()
{
	// make sure *this* is already registered
	assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);

	// submit deregistration command
	SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), pDeregistrationCmd);

	// update current registration state
	RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}