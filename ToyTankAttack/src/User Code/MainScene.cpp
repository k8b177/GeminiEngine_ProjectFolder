#include "MainScene.h"

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
#include "LevelEnum.h"


void MainScene::Initialize()
{
	pHUDManager = new HUDManager(LevelEnum::LEVEL1);
	GOTank = new Tank(pHUDManager);
	GOFloorPlane = new FloorPlane();
	pCameraController = new CameraController(GOTank, Vect(0.0f, 20.0f, -75.0f));
	pEnemySpawner = new EnemySpawner(GOTank);
	GOLegoBrick1 = new LegoBrick("Red", Vect(-200, 60, 0));
	GOLegoBrick2 = new LegoBrick("Red", Vect(15, 60, -300));
	GOLegoBrick3 = new LegoBrick("Orange", Vect(-100, 60, 200));
	GOLegoBrick4 = new LegoBrick("Yellow", Vect(-200, 60, -200));
	GOLegoBrick5 = new LegoBrick("ArmyGreen", Vect(-350, 60, 300));
	GOLegoBrick6 = new LegoBrick("Blue", Vect(-400, 60, -150));

	GOBed = new Bed();
	
	GameManager::InitializeLevel(LevelEnum::LEVEL1, pHUDManager);


	// Set Collision Pairs
	SetCollisionPair<Tank, Obstacle>();
	SetCollisionPair<Enemy, Obstacle>();
	
	SetCollisionPair<Tank, Enemy>();
	SetCollisionPair<Enemy, Bullet>();
	SetCollisionSelf<Enemy>();
	SetCollisionPair<Tank, EnemyBullet>();
	
	SetCollisionPair<Bullet, Obstacle>();
	SetCollisionPair<EnemyBullet, Obstacle>();

}

void MainScene::SceneEnd()
{
	delete pHUDManager;
	delete GOTank;
	delete GOFloorPlane;

	delete GOLegoBrick1;
	delete GOLegoBrick2;
	delete GOLegoBrick3;
	delete GOLegoBrick4;
	delete GOLegoBrick5;
	delete GOLegoBrick6;
	delete GOBed;

	delete pCameraController;
	pEnemySpawner->Cleanup();
	delete pEnemySpawner;
}