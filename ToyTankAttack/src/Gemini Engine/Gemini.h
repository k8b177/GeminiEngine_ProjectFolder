#ifndef GAME_H
#define GAME_H

#include "AzulCore.h"


class Gemini : public Engine // singleton
{
	/// \cond
	friend class GeminiAttorney;
	/// \endcond
private:
	/// \cond
	static Gemini* ptrInstance;

	static Gemini& Instance();

	// ---- BIG FOUR ---- //
	Gemini() {};
	Gemini(const Gemini&) = delete;
	Gemini& operator= (const Gemini&) = delete;
	~Gemini() = default;

	virtual void Initialize();
	virtual void LoadContent();
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();

	static float GetTime();
	/// \endcond

	///-------------------------------------------------------------------------------------------------
	/// \brief Load external resources needed for the game.
	/// 
	/// Load all the external resources you need for the game in this function AND set the start scene.  You will need to use
	/// the Load functions of the ModelManager, TextureManager, ShaderManager, and ImageManager and provide
	/// identification keys as strings. Finally, create an instance of your first scene and call SceneManager::SetNextScene(Scene*)
	/// 
	/// \par Example:
	/// 	 
	/// \code
	/// void Gemini::LoadResources()
	/// {
	///		// Load the Models
	///		ModelManager::Load("Plane", "Plane.azul");
	///		ModelManager::Load("Frigate", "space_frigate.azul");
	///		
	///		// Load the Textures
	///		TextureManager::Load("SpaceFrigateTex", "space_frigate.tga");
	///		TextureManager::Load("GridTex", "grid.tga");
	///
	///		///	Load the Images
	///		ImageManager::Load("StitchImage", TextureManager::Get("StitchTex"));
	///
	///		// Load the Shaders
	///		ShaderManager::Load("TextureFlat", "textureFlatRender");
	///		ShaderManager::Load("TextureLight", "textureLightRender");
	///		
	///		// Set the Start Scene
	///		Scene* demoScene = new MyFirstScene();
	///		SceneManager::SetNextScene(demoScene);
	///	}
	///	\endcode
	///			
	///-------------------------------------------------------------------------------------------------
	void LoadResources();

	///-------------------------------------------------------------------------------------------------
	/// \brief	Initializes the Game Window
	/// 		
	/// Use for setting up the game window and for one time, non-graphic creation.
	/// 
	///		
	///		
	///	\par Example:
	///		  
	///	\code
	///	void Gemini::GameInitialize()
	///	{
	///		// Game Window Device setup
	///		Gemini::SetWindowName("My First Scene");
	///		Gemini::SetWidthHeight(800, 600);
	///		Gemini::SetClear(0.4f, 0.4f, 0.8f, 1.0f);
	///
	///		// Use this area, for one time non-graphic creation
	///		// ...
	///	}
	///	\endcode 
	///			 
	///	\callgraph
	///			  
	///	
	///	
	///			 
	///-------------------------------------------------------------------------------------------------
	void GameInitialize();

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Gemini::GameEnd();
	///
	/// \brief	Ends the Game Window.
	/// 		
	/// Use for final clean up.
	///
	///-------------------------------------------------------------------------------------------------
	void GameEnd();


public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static int Gemini::GetHeight();
	///
	/// \brief	Gets the height of the game window.
	///
	/// \returns	The height.
	/// 			
	///-------------------------------------------------------------------------------------------------
	static int GetHeight();

	///-------------------------------------------------------------------------------------------------
	/// \fn	static int Gemini::GetWidth();
	///
	/// \brief	Gets the width of the game window.
	///
	/// \returns	The width.
	/// 			
	///-------------------------------------------------------------------------------------------------
	static int GetWidth();

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void Gemini::SetClear(float r, float g, float b, float a);
	///
	/// \brief	Sets the default background color of the window. Input is RGBA color code.
	///
	/// \param 	r	Red color value.
	/// \param 	g	Green color value.
	/// \param 	b	Blue color value.
	/// \param 	a	Alpha color value.
	/// 			
	///-------------------------------------------------------------------------------------------------
	static void SetClear(float r, float g, float b, float a);

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void Gemini::SetWidthHeight(int w, int h);
	///
	/// \brief	Sets width and height of the game window.
	///
	/// \param 	w	The width.
	/// \param 	h	The height.
	/// 			
	///-------------------------------------------------------------------------------------------------
	static void SetWidthHeight(int w, int h);

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void Gemini::SetWindowName(const char* name);
	///
	/// \brief	Sets the window name.	
	///
	/// \param 	name	The name.
	/// 				
	///-------------------------------------------------------------------------------------------------
	static void SetWindowName(const char* name);

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void Gemini::Run();
	///
	/// \brief	Runs the game loop. Called in main.cpp
	///
	///-------------------------------------------------------------------------------------------------
	static void Run(); // called in main.cpp
};

#endif