#ifndef Scene_
#define Scene_

#include "UpdatableManager.h"
#include "DrawableManager.h"
#include "AlarmableManager.h"
#include "KeyboardEventManager.h"
#include "CollisionManager.h"
#include "SceneRegistrationBroker.h"
#include "CameraManager.h"

class Updatable;
class Drawable;
class Alarmable;
class Inputable;
class CommandBase;
class Camera;

class Scene
{
	/// \cond
	friend class SceneAttorney;
	/// \endcond

private:
	/// \cond
	UpdatableManager UpdateMgr;
	DrawableManager DrawMgr;
	AlarmableManager AlarmMgr;
	KeyboardEventManager KBEventMgr;
	CollisionManager CollisionMgr;

	SceneRegistrationBroker RegistrationBrkr;
	CameraManager CamMgr;


	void Update(); // only avaiable to SceneManager
	void Draw(); // only avaiable to SceneManager

	void Register(Updatable* up);
	void Register(Drawable* dr);
	void Register(float t, AlarmableManager::ALARM_ID id, Alarmable* al);
	void Register(AZUL_KEY k, EVENT_TYPE e, Inputable* in);
	void Deregister(Updatable* up);
	void Deregister(Drawable* dr);
	void Deregister(AlarmableManager::ALARM_ID id, Alarmable* al);
	void Deregister(AZUL_KEY k, EVENT_TYPE e, Inputable* in);
	void SubmitCommand(CommandBase* cmd);
	/// \endcond

protected:

	///-------------------------------------------------------------------------------------------------
	/// \fn	template <typename C1, typename C2> void Scene::SetCollisionPair()
	///
	/// \brief	Tells the scene to watch for collisions between two GameObject types.
	/// 		
	/// \tparam	C1	A GameObject type
	/// \tparam	C2	A second GameObject type
	/// 		
	/// When calling this method, specify two kinds of GameObject's - you want to trigger callbacks when these two types collide.
	/// 
	/// \par Example:
	/// 	 In the following example, \b MainScene is a Scene that wants to watch for \b Bullet - \b Enemy collisions.
	/// 	 
	/// \code
	/// void MainScene::Initialize()
	///	{
	///		// Creating GameObjects in the scene
	///		// ...
	///
	///		// Bullet and Enemy are user-defined GameObject types
	///		SetCollisionPair<Bullet, Enemy>();
	///	}
	/// \endcode
	/// 			
	///-------------------------------------------------------------------------------------------------
	template <typename C1, typename C2>
	void SetCollisionPair()
	{
		CollisionMgr.SetCollisionPair<C1, C2>();
	}

	///-------------------------------------------------------------------------------------------------
	/// \fn	template <typename C> void Scene::SetCollisionSelf()
	///
	/// \brief	Tells the scene to watch for collisions between GameObject 's of one specified type.
	/// 		
	/// \tparam	C	A GameObject type.
	/// 		
	/// When calling this method, specify one kind of GameObject - you want to trigger a callback when an object of this type collides with another object of this type.
	///
	/// \par Example:
	/// 	 In the following example, \b MainScene is a Scene that wants to watch for \b Enemy - \b Enemy collisions.
	///
	/// \code
	/// void MainScene::Initialize()
	///	{
	///		// Creating GameObjects in the scene
	///		// ...
	///
	///		// Enemy is a user-defined GameObject type
	///		SetCollisionSelf<Enemy>();
	///	}
	/// \endcode
	/// 			
	///-------------------------------------------------------------------------------------------------
	template <typename C>
	void SetCollisionSelf()
	{
		CollisionMgr.SetCollisionSelf<C>();
	}

public:
	/// \cond
	// ---- BIG FOUR ---- //
	Scene() = default;
	Scene(const Scene&) = delete;
	Scene& operator= (const Scene&) = delete;
	virtual ~Scene() = default;
	/// \endcond

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Scene::Initialize()
	///
	/// \brief	Used for initializing the scene.
	/// 		
	/// \par
	/// 	Initialize() is called as soon as this scene begins.  Should create the necessary GameObject 's 
	/// 	for this scene.
	/// 	
	/// \par Example:
	/// 	 
	/// \code
	/// void MyFirstScene::Initialize()
	///	{
	///		// Context:
	///		//	- GOFrig is type Frigate* (a GameObject)
	///		//	- GOPlane is type Plane* (a GameObject)
	///
	///		GOFrig = new Frigate();
	///		GOPlane = new WorldPlane();
	///	}
	/// \endcode
	///
	///-------------------------------------------------------------------------------------------------
	virtual void Initialize() {};

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Scene::SceneEnd()
	///
	/// \brief	Used for ending the scene.
	/// 		
	/// \par 
	/// 	 SceneEnd() is called when the scene closes. Should delete any GameObject 's
	/// 	 in this scene and perform general cleanup.
	/// 	 
	/// \code
	/// void MyFirstScene::SceneEnd()
	/// {
	///		//Context:
	///		//	- GOFrig is type Frigate* (a GameObject)
	///		//	- GOPlane is type Plane* (a GameObject)
	///		
	///		delete GOFrig;
	///		delete GOPlane;
	/// }
	/// \endcode
	///
	///-------------------------------------------------------------------------------------------------
	virtual void SceneEnd() {};

	///-------------------------------------------------------------------------------------------------
	/// \fn	Camera* Scene::GetCurrentCamera();
	///
	/// \brief	Returns a pointer to the current Camera.
	///
	/// \returns	Null if it fails, else the current camera.
	/// 			
	/// \par Example
	/// 	 In the following example, Frigate is a GameObject with a GraphicsObject that is being rendered.
	/// 	 
	/// \code
	/// void Frigate::Draw()
	///	{
	///		// pGObjLT is type GraphicsObject_TextureLight*
	///		pGObjLT->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	///	}
	/// \endcode
	/// 			
	///------------------------------------------------------------------------------------------------
	Camera* GetCurrentCamera();

	///-------------------------------------------------------------------------------------------------
	/// \fn	Camera* Scene::Get2DCamera();
	///
	/// \brief	Returns a pointer to the 2D Camera.
	/// 		
	/// \returns	Null if it fails, else the 2D camera.
	/// 			
	///-------------------------------------------------------------------------------------------------
	Camera* Get2DCamera();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Scene::SetCurrentCamera(Camera* cam);
	///
	/// \brief	Sets current camera.
	///
	/// \param Camera* cam	The pointer to the Camera that will be set as the new current Camera.
	/// 			   
	/// \par Example
	/// 	 In the following example, CameraController is a GameObject that creates a new camera and sets the scene camera to the new camera.
	/// 	 
	/// \code
	/// CameraController::CameraController()
	/// {
	///		// mainCam is type Camera*
	///		mainCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	///		
	///		// Initialize mainCam: set viewport, set perspective, etc.
	///		// ...
	///		
	///		// Set the scene camera to be mainCam
	///		SceneManager::GetCurrentScene()->SetCurrentCamera(c);
	/// }
	/// \endcode
	/// 			   
	///-------------------------------------------------------------------------------------------------
	void SetCurrentCamera(Camera* cam);


};

#endif Scene_
