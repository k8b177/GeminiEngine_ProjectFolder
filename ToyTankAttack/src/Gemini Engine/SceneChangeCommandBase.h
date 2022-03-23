#ifndef SceneChangeCommandBase_
#define SceneChangeCommandBase_

#include "CommandBase.h"

class SceneChangeCommandBase : public CommandBase
{
public:
	// ---- BIG FOUR ---- //
	SceneChangeCommandBase() = default;
	SceneChangeCommandBase(const SceneChangeCommandBase&) = delete;
	SceneChangeCommandBase& operator= (const SceneChangeCommandBase&) = delete;
	~SceneChangeCommandBase() = default;

	virtual void Execute() = 0;
};

#endif SceneChangeCommandBase_