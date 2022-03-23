#include "Drawable.h"

#include "SceneManager.h"
#include "SceneAttorney.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"

Drawable::Drawable()
	:RegStateCurr(RegistrationState::CURRENTLY_DEREGISTERED)
{
	// creating instances of registration and deregistration commands and saving references
	pRegistrationCmd = new DrawRegistrationCommand(this);
	pDeregistrationCmd = new DrawDeregistrationCommand(this);
}

Drawable::~Drawable()
{
	// deleting instances of registration and deregistration commands
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
}

void Drawable::SetDeleteRef(DrawableManager::StorageListRef ref)
{
	this->pMyDeleteRef = ref;
}

DrawableManager::StorageListRef Drawable::GetDeleteRef()
{
	return this->pMyDeleteRef;
}

void Drawable::SceneRegistration()
{
	// make sure *this* is pending registration
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);

	// register to scene (adding to drawable manager's storage list)
	SceneAttorney::XAblesAccess::Register(SceneManager::GetCurrentScene(), this);

	// update current registration state
	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::SceneDeregistration()
{
	// make sure *this* is pending deregistration
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);

	// deregister from scene (removing from drawable manager's storage list)
	SceneAttorney::XAblesAccess::Deregister(SceneManager::GetCurrentScene(), this);

	// update current registration state
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Drawable::SubmitDrawRegistration()
{
	// make sure *this* is already deregistered
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);

	// submit registration command
	SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), pRegistrationCmd);

	// update current registration state
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDrawDeregistration()
{
	// make sure *this* is already registered
	assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);

	// submit deregistration command
	SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), pDeregistrationCmd);

	// update current registration state
	RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}