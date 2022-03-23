#ifndef GameObjectAttorney_
#define GameObjectAttorney_

#include "GameObject.h"

class GameObjectAttorney
{
	// ---- BIG FOUR ---- //
	GameObjectAttorney() = default;
	GameObjectAttorney(const GameObjectAttorney&) = delete;
	GameObjectAttorney& operator= (const GameObjectAttorney&) = delete;
	~GameObjectAttorney() = default;

	friend class GameObjectEntryCommand;
	friend class GameObjectExitCommand;

private:
	static void ConnectToScene(GameObject* go) { go->ConnectToScene(); }
	static void DisconnectFromScene(GameObject* go) { go->DisconnectFromScene(); }
};

#endif GameObjectAttorney_
