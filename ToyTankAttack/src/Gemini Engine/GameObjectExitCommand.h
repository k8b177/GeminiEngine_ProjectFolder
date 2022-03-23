#ifndef GameObjectExitCommand_
#define GameObjectExitCommand_

#include "CommandBase.h"

class GameObject;

class GameObjectExitCommand : public CommandBase
{
private:
	GameObject* ptrGO;

public:
	// ---- BIG FOUR ---- //
	GameObjectExitCommand() = delete;
	GameObjectExitCommand(const GameObjectExitCommand&) = delete;
	GameObjectExitCommand& operator= (const GameObjectExitCommand&) = delete;
	~GameObjectExitCommand() = default;

	GameObjectExitCommand(GameObject* g);


	virtual void Execute() override;
};

#endif GameObjectExitCommand_