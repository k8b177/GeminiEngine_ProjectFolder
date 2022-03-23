#include "Collidable.h"

#include "SceneAttorney.h"
#include "CollidableGroup.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"

Collidable::Collidable()
	:RegStateCurr(RegistrationState::CURRENTLY_DEREGISTERED)
{
	pRegistrationCmd = new CollisionRegistrationCommand(this);
	pDeregistrationCmd = new CollisionDeregistrationCommand(this);
}

Collidable::~Collidable()
{
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
}

void Collidable::SceneRegistration()
{
	// make sure *this* is pending registration
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);

	SceneAttorney::XAblesAccess::GetCollisionMgr()->GetColGroup(myID)->Register(this, pMyDeleteRef);

	// update current registration state
	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
	
}

void Collidable::SceneDeregistration()
{
	// make sure *this* is pending deregistration
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::XAblesAccess::GetCollisionMgr()->GetColGroup(myID)->Deregister(pMyDeleteRef);

	// update current registration state
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Collidable::SubmitCollisionRegistration()
{
	// make sure *this* is already deregistered
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);

	// submit registration command
	SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), pRegistrationCmd);

	// update current registration state
	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Collidable::SubmitCollisionDeregistration()
{
	// make sure *this* is already registered
	assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);

	// submit deregistration command
	SceneAttorney::XAblesAccess::SubmitCommand(SceneManager::GetCurrentScene(), pDeregistrationCmd);

	// update current registration state
	RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Collidable::SetColliderModel(Model* mod)
{
	pColModel = mod;
}

const CollisionVolumeBSphere& Collidable::GetBSphere()
{
	return BSphere;
}

void Collidable::UpdateCollisionData(const Matrix& mat)
{
	BSphere.ComputeData(pColModel, mat);
}