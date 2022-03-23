#ifndef GameObject_
#define GameObject_

#include "Updatable.h"
#include "Drawable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"
#include "RegistrationStateEnum.h"

class GameObjectEntryCommand;
class GameObjectExitCommand;

///-------------------------------------------------------------------------------------------------
/// \class	GameObject
/// \ingroup WHAT_IS_A_GAMEOBJECT
///
/// \brief	An object that acts in your scene - the building block for gameplay.
/// 		
/// See \ref GAMEOBJECT_INFO to learn all about GameObject 's and their capabilities.
/// 		
///-------------------------------------------------------------------------------------------------
class GameObject: public Updatable, public Drawable, public Alarmable, public Inputable, public Collidable
{	
	/// \cond
	friend class GameObjectAttorney;

private:
	RegistrationState currState;
	GameObjectEntryCommand* pRegCmd;
	GameObjectExitCommand* pDeregCmd;

	void ConnectToScene();
	void DisconnectFromScene();
	/// \endcond

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void GameObject::SceneEntry()
	///
	/// \brief	Executed when a GameObject dynamically enters a Scene.  Should "activate" the GameObject.
	/// 		
	/// This method executes the frame after GameObject::SubmitEntry() has been called.
	/// The body of the SceneEntry() method should "activate" the GameObject however the user sees fit.
	/// 
	/// \par Example:
	/// 		 In this example, a \b BulletFactory is dynamically creating \b Bullets when the player fires using a \b BulletPool.
	/// 		 When a \b Bullet is taken from the \b BulletPool, it needs to enter the scene using SceneEntry().
	/// 		 
	///		\code
	///		void Bullet::SceneEntry()
	///		{
	///			// Register for Update
	///			SubmitUpdateRegistration();
	///			
	///			// Register for Draw
	///			SubmitDrawRegistration();
	///			
	///			// Register for Alarm
	///			SubmitAlarmRegistration(3.0f, AlarmableManager::ALARM_ID::ALARM_0);
	///		}
	///		\endcode
	///					 
	///-------------------------------------------------------------------------------------------------
	virtual void SceneEntry() {};

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void GameObject::SceneExit()
	///
	/// \brief	Executed when a GameObject dynamically exits a Scene.  Should "deactivate" the GameObject.
	///
	/// This method executes the frame after GameObject::SubmitExit() has been called.
	/// The body of the SceneExit() method should "deactivate" the GameObject however the user sees fit.
	///
	/// \par Example:
	/// 		 In this example, a \b BulletFactory is dynamically recycling \b Bullets to a \b BulletPool when they are destroyed.
	/// 		 When a \b Bullet is recycled to the \b BulletPool, it needs to exit the scene using SceneExit().
	/// 		 
	///		\code
	///		void Bullet::SceneExit()
	///		{
	///			// Deregister from Update
	///			SubmitUpdateDeregistration();
	///			
	///			// Deregister from Draw
	///			SubmitDrawDeregistration();
	///
	///			// Recycle the bullet
	///			BulletFactory::BulletReturn(this);
	///		}
	///		\endcode
	///						 		 
	///-------------------------------------------------------------------------------------------------
	virtual void SceneExit() {};

	/// \cond
public:
	// ---- BIG FOUR ---- //
	GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator= (const GameObject&) = delete;
	virtual ~GameObject();
	/// \endcond

	///-------------------------------------------------------------------------------------------------
	/// \fn	void GameObject::SubmitEntry();
	///
	/// \brief	Requests that the GameObject enter the Scene.
	/// 		
	/// You should call GameObject::SceneEntry() when you want an object to dynamically enter the scene.
	/// The method will mark the GameObject as "Registered" to the Scene.
	/// During the next frame, the body of the GameObject::SceneEntry() will be called.
	/// SceneEntry() should "activate" the GameObject however the user sees fit.
	/// 
	/// \par Example:
	/// 	In this example, a \b BulletFactory is dynamically creating \b Bullets when the player fires using a \b BulletPool.
	/// 	When a \b Bullet is taken from the \b BulletPool, it needs to request to enter the Scene.
	///	 
	/// \code
	/// Bullet* BulletFactory::privCreateBullet(Matrix gunRotPos)
	///	{
	///		Bullet* b;
	///
	///		// get new or recycled bullet
	///		b = myBulletPool.GetBullet();
	///
	///		// initialize the bullet with the gun's rotPos
	///		b->Initialize(gunRotPos);
	///		
	///		// request that the bullet enter the scene
	///		// GameObject::SceneEntry() will execute the next frame
	///		b->SubmitEntry();
	///
	///		return b;
	///	}
	/// \endcode
	///
	/// \note
	/// 	  You only need to use SubmitEntry() for objects that dynamically enter the scene.
	/// 	  For objects that persist through the entire scene, you do not need to call SubmitEntry() in the constructor.
	///
	///-------------------------------------------------------------------------------------------------
	void SubmitEntry();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void GameObject::SubmitExit();
	///
	/// \brief	Requests that the GameObject exit the Scene.
	///
	/// You should call GameObject::SceneExit() when you want an object to dynamically exit the scene.
	/// The method will mark the GameObject as "Deregistered" from the Scene.
	/// During the next frame, the body of the GameObject::SceneExit() will be called.
	/// SceneExit() should "deactivate" the GameObject however the user sees fit.
	///
	/// \par Example:
	/// 		 In this example, Bullets are being created and destroyed dynamically.
	/// 		 When a \b Bullet collides with an Enemy, the Bullet requests to exit the Scene.
	///
	///		\code
	///		void Enemy::Collision(Bullet* b)
	///		{
	///			// Bullet that collided with the enemy requests to leave the scene.
	///			// Bullet::SceneExit() will be executed on the next frame.
	///			b->SubmitExit();
	///		}
	///		\endcode
	///				
	///	 \note
	/// 	  You only need to use SceneExit() for objects that dynamically exit the scene.
	/// 	  For objects that persist through the entire scene, you do not need to call SceneExit() in the destructor.
	///				
	///-------------------------------------------------------------------------------------------------
	void SubmitExit();
};


#endif GameObject_
