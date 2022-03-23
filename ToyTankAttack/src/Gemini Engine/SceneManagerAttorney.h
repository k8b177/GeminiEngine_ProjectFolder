#ifndef SceneManagerAttorney_
#define SceneManagerAttorney_

#include "SceneManager.h"

class SceneManagerAttorney
{
	// ---- BIG FOUR ---- //
	SceneManagerAttorney() = default;
	SceneManagerAttorney(const SceneManagerAttorney&) = delete;
	SceneManagerAttorney& operator= (const SceneManagerAttorney&) = delete;
	~SceneManagerAttorney() = default;

public:
	class GeminiAccess
	{
		// methods in SceneManager only available to Gemini
	private:
		friend class Gemini;
		static void Update() { SceneManager::Update(); }
		static void Draw() { SceneManager::Draw(); }
		static void Delete() { SceneManager::Delete(); }
	};

	// methods in SceneManager only available to SceneChangeCommand
	class CommandAccess
	{
	private:
		friend class SceneChangeCommand;
		static void ChangeScene(Scene* newScene) { SceneManager::ChangeScene(newScene); }
	};
};

#endif SceneManagerAttorney_
