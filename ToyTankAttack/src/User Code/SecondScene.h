

#ifndef SecondScene_
#define SecondScene_

#include "../Gemini Engine/Scene.h"

class Tank;
class FloorPlane;
class CameraController;
class EnemySpawner;
class TeddyBear;
class LegoBrick;
class HUDManager;
class ToyPlane;
class Bed;
class EnemyPlaneSpawner;

class SecondScene : public Scene
{
public:
	// ---- BIG FOUR ---- //
	SecondScene() = default;
	SecondScene(const SecondScene&) = delete;
	SecondScene& operator= (const SecondScene&) = delete;
	~SecondScene() = default;

	virtual void Initialize();
	virtual void SceneEnd();

private:
	EnemyPlaneSpawner* pEnemyPlaneSpawner;
	FloorPlane* GOFloorPlane;
	CameraController* pCameraController;
	ToyPlane* GOToyPlane;

	TeddyBear* GOTBear1;
	TeddyBear* GOTBear2;
	TeddyBear* GOTBear3;

	LegoBrick* GOLegoBrick1;
	Bed* GOBed;

	HUDManager* pHUDManager;
};

#endif SecondScene_
