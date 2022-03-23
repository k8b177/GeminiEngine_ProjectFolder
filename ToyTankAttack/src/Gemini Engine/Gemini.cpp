#include "AzulCore.h"
#include "Gemini.h"

#include "ShaderManagerAttorney.h"
#include "TextureManagerAttorney.h"
#include "ModelManagerAttorney.h"
#include "SceneManagerAttorney.h"
#include "TimeManagerAttorney.h"
#include "VisualizerAttorney.h"
#include "ImageManagerAttorney.h"
#include "SpriteFontManagerAttorney.h"
#include "ScreenLogAttorney.h"
#include "GodCamControllerAttorney.h"

//-----------------------------------------------------------------------------
// Singleton Setup
//		Initializing the ptrInstance to null and setting up the Instance()
//		method
//-----------------------------------------------------------------------------
Gemini* Gemini::ptrInstance = nullptr;

Gemini& Gemini::Instance()
{
	if (!ptrInstance)
		ptrInstance = new Gemini();
	return *ptrInstance;
}

//-----------------------------------------------------------------------------
// Gemini::Run
//		Creates, runs, and deletes the Gemini engine instance. Called in main.cpp
//-----------------------------------------------------------------------------
void Gemini::Run()
{
	// creating the instance and running
	Instance().run();

	// deleting the instance
	delete ptrInstance;
}

//-----------------------------------------------------------------------------
// Accessors
//		Functionalites available to user via static public accessors
//-----------------------------------------------------------------------------
int Gemini::GetHeight()
{
	return Instance().getHeight();
}

float Gemini::GetTime()
{
	return Instance().GetTimeInSeconds();
}

int Gemini::GetWidth()
{
	return Instance().getWidth();
}

void Gemini::SetClear(float r, float g, float b, float a)
{
	Instance().SetClearColor(r, g, b, a);
}

void Gemini::SetWidthHeight(int w, int h)
{
	Instance().setWidthHeight(w, h);
}

void Gemini::SetWindowName(const char* name)
{
	Instance().setWindowName(name);
}


//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Gemini::Initialize()
{
	this->GameInitialize();
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Gemini::LoadContent()
{
	this->LoadResources(); // user defined --> Loading all the models, textures, & shaders
	// user sets the start scene at the end of LoadResources
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Gemini::Update()
{
	TimeManagerAttorney::ProcessTime();
	SceneManagerAttorney::GeminiAccess::Update();
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Gemini::Draw()
{
	SceneManagerAttorney::GeminiAccess::Draw();
	VisualizerAttorney::GeminiAccess::VisualizeAll();
	ScreenLogAttorney::Render();
}

//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Gemini::UnLoadContent()
{
	// Cleanup for SceneManager
	SceneManagerAttorney::GeminiAccess::Delete();

	// Cleanup for Shaders, Textures, Models, Images, and SpriteFonts
	ShaderManagerAttorney::Delete();
	TextureManagerAttorney::Delete();
	ModelManagerAttorney::Delete();
	ImageManagerAttorney::Delete();
	SpriteFontManagerAttorney::Delete();

	// Cleanup for TimeManager
	TimeManagerAttorney::Delete();

	// Cleanup for Visualizer
	VisualizerAttorney::GeminiAccess::Delete();

	// Cleanup for ScreenLog
	ScreenLogAttorney::Delete();

	// Cleanup for GodCamController
	GodCamControllerAttorney::Delete();


	// Call GameEnd (User-Defined)
	Instance().GameEnd();
}


