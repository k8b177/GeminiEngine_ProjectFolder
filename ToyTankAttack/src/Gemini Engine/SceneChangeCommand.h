#ifndef SceneChangeCommand_
#define SceneChangeCommand_

#include "SceneChangeCommandBase.h"

class Scene;

class SceneChangeCommand : public SceneChangeCommandBase
{
private:
	Scene* nextScene;
public:
	// ---- BIG FOUR ---- //
	SceneChangeCommand() = default;
	SceneChangeCommand(const SceneChangeCommand&) = delete;
	SceneChangeCommand& operator= (const SceneChangeCommand&) = delete;
	~SceneChangeCommand() = default;

	virtual void Execute() override;
	void SetNextScene(Scene* ns);
};

#endif SceneChangeCommand_