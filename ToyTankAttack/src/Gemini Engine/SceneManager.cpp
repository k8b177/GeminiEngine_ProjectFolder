#include "SceneManager.h"

#include "SceneAttorney.h"
#include "SceneNull.h"
#include "SceneChangeCommand.h"
#include "SceneChangeNullCommand.h"


//-----------------------------------------------------------------------------
// Singleton Setup
//		Initializing the ptrInstance to null and setting up the Instance()
//		method
//-----------------------------------------------------------------------------
SceneManager* SceneManager::ptrInstance = nullptr;

SceneManager& SceneManager::Instance()
{
	if (!ptrInstance)
		ptrInstance = new SceneManager();
	return *ptrInstance;
}

//-----------------------------------------------------------------------------
// Constructor
//		Creating a Scene Null Scene for the starting scene
//-----------------------------------------------------------------------------
SceneManager::SceneManager()
{
	ptrCurrentScene = new SceneNull(); // default scene to start

	pSceneChangeCmd = new SceneChangeCommand();
	pSceneChangeNullCmd = new SceneChangeNullCommand();

	pCurrentSceneChangeCmd = pSceneChangeNullCmd;
}

//-----------------------------------------------------------------------------
// Destructor
//		
//-----------------------------------------------------------------------------
SceneManager::~SceneManager()
{
	delete pSceneChangeCmd;
	delete pSceneChangeNullCmd;
}

//-----------------------------------------------------------------------------
// SceneManager::GetCurrentScene()
//		Returns a pointer to the current active scene
//-----------------------------------------------------------------------------
Scene* SceneManager::GetCurrentScene()
{
	return Instance().ptrCurrentScene;
}


//-----------------------------------------------------------------------------
// SceneManager::SetNextScene(Scene* ns)
//		
//-----------------------------------------------------------------------------
void SceneManager::privSetNextScene(Scene* ns)
{
	pSceneChangeCmd->SetNextScene(ns); // pass pointer to next scene to command
	pCurrentSceneChangeCmd = pSceneChangeCmd; // update command pointer so change command will execute at top of next frame
}

//-----------------------------------------------------------------------------
// SceneManager::privChangeScene(Scene* s)
//		
//-----------------------------------------------------------------------------
void SceneManager::privChangeScene(Scene* s)
{
	ptrCurrentScene->SceneEnd(); // call scene end on old scene
	delete ptrCurrentScene; // delete old scene

	ptrCurrentScene = s; // update current scene pointer
	ptrCurrentScene->Initialize(); // initialize new scene

	pCurrentSceneChangeCmd = pSceneChangeNullCmd; // set CurrentSceneChangeCommand back to null
}

//-----------------------------------------------------------------------------
// SceneManager::Update()
//		Calls Update() on the ptrCurrentScene
//-----------------------------------------------------------------------------
void SceneManager::privUpdate()
{
	pCurrentSceneChangeCmd->Execute(); // either does nothing or a scene change

	SceneAttorney::Manager::Update(ptrCurrentScene);
}

//-----------------------------------------------------------------------------
// SceneManager::Draw()
//		Calls Draw() on the ptrCurrentScene
//-----------------------------------------------------------------------------
void SceneManager::Draw()
{
	SceneAttorney::Manager::Draw(Instance().ptrCurrentScene);
}

//-----------------------------------------------------------------------------
// SceneManager::Delete()
//		Clean-up.  Calls SceneEnd() on the ptrCurrentScene, deletes the 
//		ptrCurrentScene and deletes the ptrInstance
//-----------------------------------------------------------------------------
void SceneManager::Delete()
{
	Instance().ptrCurrentScene->SceneEnd();
	delete Instance().ptrCurrentScene;

	delete ptrInstance;
}