

#ifndef MainScene_
#define MainScene_

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

class MainScene : public Scene
{
public:
	// ---- BIG FOUR ---- //
	MainScene() = default;
	MainScene(const MainScene&) = delete;
	MainScene& operator= (const MainScene&) = delete;
	~MainScene() = default;

	virtual void Initialize();
	virtual void SceneEnd();

private:
	Tank* GOTank;

	FloorPlane* GOFloorPlane;
	LegoBrick* GOLegoBrick1;
	LegoBrick* GOLegoBrick2;
	LegoBrick* GOLegoBrick3;
	LegoBrick* GOLegoBrick4;
	LegoBrick* GOLegoBrick5;
	LegoBrick* GOLegoBrick6;
	Bed* GOBed;

	CameraController* pCameraController;
	EnemySpawner* pEnemySpawner;
	HUDManager* pHUDManager;
};

#endif MainScene_
