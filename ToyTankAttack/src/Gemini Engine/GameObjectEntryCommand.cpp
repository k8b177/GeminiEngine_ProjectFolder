#include "GameObjectEntryCommand.h"

#include "GameObjectAttorney.h"

GameObjectEntryCommand::GameObjectEntryCommand(GameObject* go)
	:ptrGO(go)
{}

void GameObjectEntryCommand::Execute()
{
	GameObjectAttorney::ConnectToScene(ptrGO);
}