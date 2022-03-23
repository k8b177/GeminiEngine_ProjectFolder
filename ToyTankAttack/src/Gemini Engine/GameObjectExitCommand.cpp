#include "GameObjectExitCommand.h"

#include "GameObjectAttorney.h"

GameObjectExitCommand::GameObjectExitCommand(GameObject* go)
	:ptrGO(go)
{}

void GameObjectExitCommand::Execute()
{
	GameObjectAttorney::DisconnectFromScene(ptrGO);
}