#ifndef Drawable_
#define Drawable_

#include "RegistrationStateEnum.h"
#include "DrawableManager.h"

class DrawRegistrationCommand;
class DrawDeregistrationCommand;

class Drawable
{
	/// \cond
	friend class DrawableAttorney;

private:
	RegistrationState RegStateCurr; // current registration state

	DrawRegistrationCommand* pRegistrationCmd; // pointer to instance of registration command
	DrawDeregistrationCommand* pDeregistrationCmd; // pointer to instance of deregistration command

	DrawableManager::StorageListRef pMyDeleteRef; // pointer to this object's iterator in DrawableManager list
												   // used for fast delete in DrawableManager

	void SetDeleteRef(DrawableManager::StorageListRef ref); // only available to DrawableManager
	DrawableManager::StorageListRef GetDeleteRef(); // only available to DrawableManager
	/// \endcond

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Drawable::Draw()
	///
	/// \brief	The code that is called once per frame for the GameObject AFTER all Updates have been called. 
	/// 
	/// \par
	/// 	Only gets called if GameObject has submitted for Draw Registration (see Drawable::SubmitDrawRegistration())
	/// 	
	/// \note 1. This method is meant only for rendering Graphics Objects to the screen.  Other computations should be avoided here.
	/// 	    
	///	\note 2. 2D GeminiSprite 's SHOULD NOT be rendered here.  Render all 2D sprites in Drawable::Draw2D() to ensure they are rendered after all 3D objects have been rendered.  
	/// 	   
	///	\note 3. Render method requires a pointer to the current camera.  Use SceneManager::GetCurrentScene->GetCurrentCamera() to access the pointer.
	///
	/// \code
	/// void Frigate::Draw()
	/// {
	///		// Context:
	///		// - pGObjLT is type GraphicsObject_TextureLight*
	///		
	/// 	pGObjLT->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	/// }
	/// \endcode
	/// 		
	///-------------------------------------------------------------------------------------------------
	virtual void Draw() {}; // only available to DrawableManager

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Drawable::Draw2D()
	///
	/// \brief	The code that is called once per frame for the GameObject AFTER all Updates and all the Draws have been called. 
	/// 
	/// \par
	/// 	Only gets called if GameObject has submitted for Draw Registration (see Drawable::SubmitDrawRegistration())
	/// 	
	/// \note 1. This method is meant only for rendering 2D GeminiSprite 's to the screen.  Other computations should be avoided here.
	///	
	///	\note 2. 3D Graphics Objects SHOULD NOT be rendered here.  Render all 3D objects in Drawable::Draw() to ensure they are rendered before 2D objects are rendered.  
	/// 	 
	/// \code
	/// void HUDManager::Draw2D()
	///	{
	///		// Context:
	///		// -pStitchSprite is type GeminiSprite*
	///		
	///		pStitchSprite->Render();
	///	}
	/// \endcode
	/// 		
	///-------------------------------------------------------------------------------------------------
	virtual void Draw2D() {}; // only available to DrawableManager

	/// \cond
	void SceneRegistration(); // inaccessible to user; user must use SubmitDrawRegistration()
	void SceneDeregistration(); // inaccessible to user; user must use SubmitDrawDeregistration()
	/// \endcond

public:
	/// \cond
	// ---- BIG FOUR ---- //
	Drawable();
	Drawable(const Drawable&) = delete;
	Drawable& operator= (const Drawable&) = delete;
	virtual ~Drawable();
	/// \endcond

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Drawable::SubmitDrawRegistration();
	/// 	
	/// \brief	Requests the GameObject to be added to the list of GameObjects Drawn every frame.
	/// 		
	/// \note Only GameObject 's who have submitted for Draw Registration will have their Draw method called every frame.
	/// 	  
	/// \code
	/// Frigate::Frigate()
	/// {
	///		// ... other initialization stuff for the Frigate
	///		
	///		Drawable::SubmitDrawRegistration();
	/// }
	/// \endcode
	/// 		
	///-------------------------------------------------------------------------------------------------
	void SubmitDrawRegistration();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Drawable::SubmitDrawDeregistration();
	///
	/// \brief	Requests the GameObject to be removed from the list of GameObjects Drawn every frame.
	/// 		
	/// \note Once a GameObject has submitted for Draw Deregistration, it will no longer have its Draw method called once per frame.
	/// 	
	/// \code
	/// void Bullet::SceneExit()
	///	{
	///		// When Bullet leaves the scene, it should no longer Draw.
	///		Drawable::SubmitDrawDeregistration();
	///	}
	/// \endcode	
	/// 
	void SubmitDrawDeregistration();

};


#endif Drawable_
