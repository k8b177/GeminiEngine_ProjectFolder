#ifndef SceneChangeNullCommand_
#define SceneChangeNullCommand_

#include "SceneChangeCommandBase.h"

class SceneChangeNullCommand : public SceneChangeCommandBase
{
public:
	// ---- BIG FOUR ---- //
	SceneChangeNullCommand() = default;
	SceneChangeNullCommand(const SceneChangeNullCommand&) = delete;
	SceneChangeNullCommand& operator= (const SceneChangeNullCommand&) = delete;
	~SceneChangeNullCommand() = default;

	virtual void Execute() override {}; // does nothing - compiled to a no-op
};

#endif SceneChangeNullCommand_