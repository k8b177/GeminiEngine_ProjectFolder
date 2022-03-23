#include "SceneRegistrationBroker.h"

#include "CommandBase.h"

void SceneRegistrationBroker::addCommand(CommandBase* cmd)
{
	lstCommands.push_back(cmd);
}

void SceneRegistrationBroker::ExecuteCommands()
{
	for (CommandBase* cmd : lstCommands)
	{
		cmd->Execute();
	}

	lstCommands.clear();
}