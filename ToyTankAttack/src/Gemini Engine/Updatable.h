#ifndef Updateable_
#define Updateable_

#include "RegistrationStateEnum.h"
#include "UpdatableManager.h"

class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class Updatable
{
	/// \cond
	friend class UpdatableAttorney;

private:
	RegistrationState RegStateCurr; // current registration state

	UpdateRegistrationCommand* pRegistrationCmd; // pointer to instance of registration command
	UpdateDeregistrationCommand* pDeregistrationCmd; // pointer to instance of deregistration command


	UpdatableManager::StorageListRef pMyDeleteRef; // pointer to this object's iterator in UpdatableManager list
												   // used for fast delete in UpdatableManager

	void SetDeleteRef(UpdatableManager::StorageListRef ref); // only available to UpdateManager
	UpdatableManager::StorageListRef GetDeleteRef(); // only available to UpdateManager
	/// \endcond


	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Updatable::Update()
	///
	/// \brief	The code that is called once per frame for the GameObject. 
	/// 
	/// \par
	/// 	Only gets called if GameObject has submitted for Update Registration (see GameObject::Updatable::SubmitUpdateRegistration())
	///
	/// \code
	/// void Frigate::Update()
	/// {
	/// 	// Ship Rotation movement
	///		if (Keyboard::GetKeyState(AZUL_KEY::KEY_J))
	///		{
	///			ShipRotTrans = Matrix(ROT_Y, ShipRotAng) * ShipRotTrans;
	///		}
	///		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_L))
	///		{
	///			ShipRotTrans = Matrix(ROT_Y, -ShipRotAng) * ShipRotTrans;
	///		}
	///
	///		// Ship translation movement
	///		if (Keyboard::GetKeyState(AZUL_KEY::KEY_I))
	///		{
	///			ShipRotTrans = Matrix(TRANS, Vect(0, 0, ShipTransSpeed)) * ShipRotTrans;
	///		}
	///		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K))
	///		{
	///			ShipRotTrans = Matrix(TRANS, Vect(0, 0, -ShipTransSpeed)) * ShipRotTrans;
	///		}
	///
	///		// Spaceship adjust matrix
	///		Matrix world = ShipScale * ShipRotTrans;
	///		// Update the world information of the graphics object
	///		pGObjLT->SetWorld(world);
	///	}
	/// \endcode
	/// 		
	///-------------------------------------------------------------------------------------------------
	virtual void Update() {}; // only available to UpdateManager

	/// \cond
	void SceneRegistration(); // register to scene - inaccessible to user; user must use SubmitUpdateRegistration
	void SceneDeregistration(); // deregister from scene - inaccessible to user; user must use SubmitUpdateDeregistration
	/// \endcond

public:
	/// \cond
	// ---- BIG FOUR ---- //
	Updatable();
	Updatable(const Updatable&) = delete;
	Updatable& operator= (const Updatable&) = delete;
	virtual ~Updatable();
	/// \endcond


	///-------------------------------------------------------------------------------------------------
	/// \fn	void Updatable::SubmitUpdateRegistration();
	///
	/// \brief	Requests the GameObject to be added to the list of GameObjects Updated every frame.
	/// 		
	/// \note Only GameObject 's who have submitted for Update Registration will have their Update method called every frame (See Updatable::SubmitUpdateRegistration()).
	/// 	  
	/// \code
	/// Frigate::Frigate()
	/// {
	///		// ... other initialization stuff for the Frigate
	///		
	///		Updatable::SubmitUpdateRegistration();
	/// }
	/// \endcode
	/// 		
	///-------------------------------------------------------------------------------------------------
	void SubmitUpdateRegistration();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Updatable::SubmitUpdateDeregistration();
	///
	/// \brief	Requests the GameObject to be removed from the list of GameObjects Updated every frame.
	/// 		
	/// \note Once a GameObject has submitted for Update Deregistration, it will no longer have it's Update method called once per frame.
	/// 	
	/// \code
	/// void Bullet::SceneExit()
	///	{
	///		// When Bullet leaves the scene, it should no longer Update.
	///		Updatable::SubmitUpdateDeregistration();
	///	}
	/// \endcode	
	/// 			
	void SubmitUpdateDeregistration();

};


#endif Updateable_
