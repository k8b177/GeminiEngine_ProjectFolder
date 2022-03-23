#include "SceneChangeCommand.h"

#include "SceneManagerAttorney.h"

void SceneChangeCommand::SetNextScene(Scene* ns)
{
	nextScene = ns;
}

void SceneChangeCommand::Execute()
{
	SceneManagerAttorney::CommandAccess::ChangeScene(nextScene);
}