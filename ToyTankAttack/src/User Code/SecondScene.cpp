#include "SecondScene.h"

#include "Tank.h"
#include "FloorPlane.h"
#include "CameraController.h"
#include "EnemySpawner.h"
#include "TeddyBear.h"
#include "LegoBrick.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "HUDManager.h"
#include "Obstacle.h"
#include "ToyPlane.h"
#include "Bed.h"
#include "GameManager.h"
#include "Bomb.h"
#include "LevelEnum.h"
#include "EnemyPlaneSpawner.h"
#include "EnemyPlane.h"


void SecondScene::Initialize()
{
	pHUDManager = new HUDManager(LevelEnum::LEVEL2);
	GOToyPlane = new ToyPlane(pHUDManager);
	pCameraController = new CameraController(GOToyPlane, Vect(75.0f, 0.0f, 20.0f));

	GOToyPlane->SetCameraController(pCameraController);

	pEnemyPlaneSpawner = new EnemyPlaneSpawner(GOToyPlane);


	GOTBear1 = new TeddyBear(0.85f, Vect(-350.0f, 0, -350.0f));
	GOTBear2 = new TeddyBear(2.0f, Vect(-200.0f, 0, 250.0f));
	GOTBear3 = new TeddyBear(-0.75f, Vect(300.0f, 0, -275.0f));

	// Decorations
	//GOLegoBrick1 = new LegoBrick();
	GOBed = new Bed();
	GOFloorPlane = new FloorPlane();

	GameManager::InitializeLevel(LevelEnum::LEVEL2, pHUDManager);

	SetCollisionPair<EnemyPlane, Bullet>();
	SetCollisionPair<EnemyPlane, ToyPlane> ();
	SetCollisionPair<TeddyBear, Bomb>();
}

void SecondScene::SceneEnd()
{
	delete pHUDManager;
	delete GOFloorPlane;
	delete GOLegoBrick1;
	delete GOBed;
	delete GOToyPlane;

	delete pCameraController;

	delete GOTBear1;
	delete GOTBear2;
	delete GOTBear3;

	pEnemyPlaneSpawner->Cleanup();
	delete pEnemyPlaneSpawner;
}