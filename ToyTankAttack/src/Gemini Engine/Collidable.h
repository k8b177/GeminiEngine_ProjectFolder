#ifndef Collidable_
#define Collidable_

#include "CollisionManager.h"
#include "SceneAttorney.h"
#include "CollidableGroup.h"
#include "RegistrationStateEnum.h"
#include "DebugOut.h"
#include "CollisionVolumeBSphere.h"

class CollisionRegistrationCommand;
class CollisionDeregistrationCommand;
class Model;

class Collidable
{
	/// \cond
	friend class CollidableAttorney;

private:
	// --- Registration --- //
	RegistrationState RegStateCurr; // current registration state

	CollisionRegistrationCommand* pRegistrationCmd; // pointer to instance of registration command
	CollisionDeregistrationCommand* pDeregistrationCmd; // pointer to instance of deregistration command

	CollisionManager::GemTypeID myID = CollisionManager::GEMID_UNDEFINED;

	CollidableGroup::CollidableCollectionRef pMyDeleteRef;	// pointer to this object's iterator in CollidableGroup list
															// used for fast delete in CollidableGroup

	void SceneRegistration(); // register to scene - inaccessible to user; user must use SubmitCollidableRegistration
	void SceneDeregistration(); // deregister from scene - inaccessible to user; user must use SubmitCollidableDeregistration

	// --- Collision --- //
	CollisionVolumeBSphere BSphere;
	Model* pColModel;
	/// \endcond

protected:

	///-------------------------------------------------------------------------------------------------
	/// \fn	template <typename C> void Collidable::SetCollidableGroup()
	///
	/// \brief	Sets collidable group that the GameObject should be associated with for collision testing.
	///
	/// \tparam	C	Type of the c.
	/// 			
	/// If a GameObject is watching for collision, you also need to indicate which \b CollidableGroup it is associated with.
	/// You must manually specify this for each of your GameObject 's.
	/// 
	/// \par SetCollidableGroup Example:
	///		In the following example, the Scene wants to watch for \b Bullet - \b Enemy Collisions.
	///		You must specify that the \b Bullet GameObject is part of the \b Bullet \b CollidableGroup and the \b Enemy GameObject is part of the \b Enemy \b CollidableGroup.
	///		GeminiEngine will create these groups internally, you just need to specify which GameObject type the group is associated with.
	/// 
	/// \code
	/// Bullet::Bullet()
	/// {
	/// 	// Other initialization
	/// 	// ...
	/// 
	/// 	// Set the Bullet to be part of the Bullet CollidableGroup
	/// 	SetCollidableGroup<Bullet>();
	/// }
	/// 
	/// Enemy::Enemy()
	/// {
	/// 	// Other initialization
	/// 	// ...
	/// 
	/// 	// Set the Enemy to be part of the Enemy CollidableGroup
	/// 	SetCollidableGroup<Enemy>();
	/// }
	/// \endcode
	/// 
	/// \note
	/// 	  Usually, the \b CollidableGroup type should match the GameObject 's type (\b Bullet is in the \b Bullet \b CollidableGroup, \b Enemy is in the \b Enemy \b CollidableGroup ).
	/// 	  BUT there is nothing stopping you from putting a GameObject in a \b CollidableGroup that does not match its type.
	/// 	  For instance, if you have more than one type of \b Enemy (a \b Wizard and an \b Elf), you could set their \b CollidableGroup to be the \b Enemy \b CollidableGroup.
	/// 	  If other GameObject 's are watching for collisions with \b Enemies , then the callback will be triggered when they collide with a \b Wizard or an \b Elf .
	/// 	  This kind of grouping could be helpful depending on your game's needs.
	/// 			
	///-------------------------------------------------------------------------------------------------
	template <typename C>
	void SetCollidableGroup()
	{
		myID = SceneAttorney::XAblesAccess::GetCollisionMgr()->GetTypeID<C>();
		//DebugMsg::out("Type ID set to: %i\n", myID);
	}

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Collidable::SetColliderModel(Model* mod);
	///
	/// \brief	Sets collider model for the GameObject.
	/// 		
	/// \param Model*	mod	The Model that represents the GameObject for collision testing.
	/// 		
	/// If a GameObject is watching for a collision, you need to indicate which Model represents the GameObject.
	/// A Bounding Geometry will be created for this Model.
	/// If you complete the collision setup process, you will be notified when the Bounding Geometry for this Model intersects with another Bounding Geometry associated with GameObject 's whose collision you care about.
	/// 	
	/// \par Example:
	/// 	 In the following example, Bullet is a GameObject getting ready for collisions.
	/// 	 In its constructor, it creates a GraphicsObject and sets its model as the Collider Model.
	/// 
	/// \code
	/// Bullet::Bullet()
	/// 
	/// 	// Creating Graphics Object for the Bullet
	/// 	// pGObj_Bullet is type GraphicsObject_TextureLight*
	/// 	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	/// 	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	/// 	Texture* pBulletTex = TextureManager::Get("BulletTex");
	/// 	pGObj_Bullet = new GraphicsObject_TextureLight(ModelManager::Get("Bullet"), ShaderManager::Get("TextureLight"), pBulletTex, pBulletTex, LightColor, LightPos);
	/// 
	/// 	// Setting the colllider model
	/// 	// A Bounding Sphere that best respresents the model will be used for collision tests
	/// 	SetColliderModel(pGObj_Bullet->getModel());
	/// }
	/// \endcode
	/// 
	/// \note
	/// 	1. The current version of GeminiEngine only calculates Bounding Sphere collisions. GeminiEngine will approximate the best fitting Bounding Sphere to match the Model you set. The resulting collision tests are efficient but inaccurate. More Bounding Geometries will be available soon.  
	/// 	2. You must set a \b Collider \b Model for every GameObject that wants to watch for collisions.   
	/// 
	///-------------------------------------------------------------------------------------------------
	void SetColliderModel(Model* mod);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Collidable::UpdateCollisionData(const Matrix& mat);
	///
	/// \brief	Updates the transform information of the Bounding Geometry of the GameObject to the matrix passed in.
	///
	/// \param 	mat	The new transform matrix of the Bounding Geometry.
	/// 			
	/// If a GameObject is set up to watch for collisions, you must call Collidable::UpdateCollisionData(const Matrix& mat) whenever your GameObject moves and pass in the world matrix of the GameObject.
	/// This way GeminiEngine can adjust the Bounding Geometry appropriately and check for intersections.
	/// 
	/// \par Example:
	///		 In the following example, the \b Bullet is set up for collision.
	///		 Whenever the \b Bullet 's transform changes during Update(), its Bounding Geometry transform also needs to be updated.
	///	
	/// \code
	/// void Bullet::Update()
	/// {
	/// 	// Adjusting the Bullet's World Matrix
	/// 	BulletRotTrans = Matrix(TRANS, Vect(0, 0, BulletSpeed)) * BulletRotTrans; // go forward at constant speed
	/// 	Matrix world = BulletScale * BulletRotTrans;
	/// 
	/// 	// pGObj_Bullet is a Graphics Object representing the bullet (type GraphicsObject_TextureLight*)
	/// 	// Updating the world matrix for the Graphics Object
	/// 	pGObj_Bullet->SetWorld(world);
	/// 
	/// 	// Updating the Bounding Geometry for the Bullet - passing in the Bullet's updated world matrix
	/// 	// The Bounding Geometry will move in tandem with the Bullet
	/// 	UpdateCollisionData(world);
	/// }
	/// \endcode
	/// 
	/// \note
	/// 	 1. The current version of GeminiEngine uses Bounding Spheres exclusively for collision testing. UpdateCollisionData will adjust the sphere according to match the world matrix you provide. More Bounding Geometries will be available soon.  
	/// 	 2. If your GameObject does not move, you do not need to update the collision data every frame.  Call UpdateCollisionData once when you place the object in the world.
	/// 
	///-------------------------------------------------------------------------------------------------
	void UpdateCollisionData(const Matrix& mat);

public:
	/// \cond
	// ---- BIG FOUR ---- //
	Collidable();
	Collidable(const Collidable&) = delete;
	Collidable& operator= (const Collidable&) = delete;
	virtual ~Collidable();
	/// \endcond

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Collidable::SubmitCollisionRegistration();
	///
	/// \brief	Submit collision registration
	/// 		
	/// For a GameObject to actively watching for collisions, it must submit a \b Collision \b Registration.
	/// While registered for collision, collision callbacks for the object will be enabled.
	/// 
	/// \par Example:
	///		In the following example, the \b Bullet GameObject registers for Collision when it enters the Scene.
	///		
	///		\code
	///		void Bullet::SceneEntry()
	///		{
	///			Collidable::SubmitCollisionRegistration();
	///		}
	///		\endcode
	///
	///-------------------------------------------------------------------------------------------------
	void SubmitCollisionRegistration();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Collidable::SubmitCollisionDeregistration();
	///
	/// \brief	Submit collision deregistration
	/// 		
	/// Submit a \b Collision \b Deregistration if you no longer wish to watch for Collisions.
	///
	///-------------------------------------------------------------------------------------------------
	void SubmitCollisionDeregistration();

	///-------------------------------------------------------------------------------------------------
	/// \fn	const CollisionVolumeBSphere& Collidable::GetBSphere();
	///
	/// \brief	Gets BoundingSphere for this GameObject.
	///
	/// \returns	Reference to the BoundingSphere for this GameObject.
	/// 			
	///-------------------------------------------------------------------------------------------------
	const CollisionVolumeBSphere& GetBSphere();

};


#endif Collidable_
