#ifndef GameObjectEntryCommand_
#define GameObjectEntryCommand_

#include "CommandBase.h"

class GameObject;

class GameObjectEntryCommand : public CommandBase
{
private:
	GameObject* ptrGO;

public:
	// ---- BIG FOUR ---- //
	GameObjectEntryCommand() = delete;
	GameObjectEntryCommand(const GameObjectEntryCommand&) = delete;
	GameObjectEntryCommand& operator= (const GameObjectEntryCommand&) = delete;
	~GameObjectEntryCommand() = default;

	GameObjectEntryCommand(GameObject* g);


	virtual void Execute() override;
};

#endif GameObjectEntryCommand_