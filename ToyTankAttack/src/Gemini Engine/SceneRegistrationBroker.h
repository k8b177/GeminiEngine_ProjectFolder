#ifndef SceneRegistrationBroker_
#define SceneRegistrationBroker_

#include <list>

class CommandBase;

class SceneRegistrationBroker
{
private:
	using CommandList = std::list<CommandBase*>;
	CommandList lstCommands;

public:
	// ---- BIG FOUR ---- //
	SceneRegistrationBroker() = default;
	SceneRegistrationBroker(const SceneRegistrationBroker&) = delete;
	SceneRegistrationBroker& operator= (const SceneRegistrationBroker&) = delete;
	~SceneRegistrationBroker() = default;

	void addCommand(CommandBase* c);
	void ExecuteCommands();
};


#endif SceneRegistrationBroker_