#ifndef SceneManager_
#define SceneManager_

class Scene;
class SceneChangeCommand;
class SceneChangeNullCommand;
class SceneChangeCommandBase;

class SceneManager // singleton (for now at least)
{
	/// \cond
	friend class SceneManagerAttorney;
	/// \endcond

private:
	/// \cond
	static SceneManager* ptrInstance;

	static SceneManager& Instance();

	// ---- BIG FOUR ---- //
	SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator= (const SceneManager&) = delete;
	~SceneManager();

	// ---- PRIVATE MEMBER VARS ---- //
	Scene* ptrCurrentScene;
	SceneChangeCommand* pSceneChangeCmd;
	SceneChangeNullCommand* pSceneChangeNullCmd;
	SceneChangeCommandBase* pCurrentSceneChangeCmd;

	static void Delete();
	static void Draw();
	static void ChangeScene(Scene* s) { Instance().privChangeScene(s); }
	static void Update() { Instance().privUpdate(); }

	void privUpdate();
	void privChangeScene(Scene* s);
	void privSetNextScene(Scene* ns);
	/// \endcond

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static Scene* SceneManager::GetCurrentScene();
	///
	/// \brief	Returns a pointer to the current scene.
	///
	/// \returns	Null if it fails, else the current scene.
	/// 			
	///-------------------------------------------------------------------------------------------------
	static Scene* GetCurrentScene();

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void SceneManager::SetNextScene(Scene* ns)
	///
	/// \brief	Sets the next scene.
	/// 		
	/// \par
	/// When called, the curent scene will change to the \b ns scene on the next frame.
	///
	/// \param Scene* ns	The pointer to the scene that will be set as the next scene.
	/// 				
	///-------------------------------------------------------------------------------------------------
	static void SetNextScene(Scene* ns) { Instance().privSetNextScene(ns); }
};

#endif SceneManager_