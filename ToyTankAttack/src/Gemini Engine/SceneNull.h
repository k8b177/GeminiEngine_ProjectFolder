
// Dummy Scene = does nothing
// Used as initial game scene, then user sets their beginning scene

#ifndef SceneNull_
#define SceneNull_

#include "Scene.h"

class SceneNull : public Scene
{
public:
	// ---- BIG FOUR ---- //
	SceneNull() = default;
	SceneNull(const SceneNull&) = delete;
	SceneNull& operator= (const SceneNull&) = delete;
	~SceneNull() = default;

	virtual void Initialize() {};
	virtual void SceneEnd() {};

};

#endif SceneNull_
