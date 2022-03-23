
#include "GameManager.h"

#include "../Gemini Engine/SceneManager.h"
#include "SecondScene.h"
#include "HUDManager.h"


GameManager* GameManager::ptrInstance = nullptr;

GameManager& GameManager::Instance()
{
	if (!ptrInstance)
		ptrInstance = new GameManager();
	return *ptrInstance;
}

GameManager::GameManager()
{
	SubmitKeyRegistration(AZUL_KEY::KEY_N, EVENT_TYPE::KEY_PRESS);
}

GameManager::~GameManager()
{}


void GameManager::privInitializeLevel(LevelEnum level, HUDManager* p)
{
	pHUDManager = p;
	currLevel = level;
	if (level == LevelEnum::LEVEL1)
	{
		numEnemiesKilled = 0;
		numEnemiesToKill = 5;
	}
	else if (level == LevelEnum::LEVEL2)
	{
		numEnemiesKilled = 0;
		numEnemiesToKill = 3;
	}
}

int GameManager::GetNumEnemiesToKill()
{
	return Instance().numEnemiesToKill;
}

int GameManager::GetNumEnemiesKilled()
{
	return Instance().numEnemiesKilled;
}


void GameManager::Delete()
{
	delete Instance().ptrInstance;
}

void GameManager::EnemyKilled()
{
	GameManager& I = Instance();
	I.numEnemiesKilled++;

	// if objective complete
	if (I.numEnemiesKilled >= I.numEnemiesToKill)
	{
		// change to level 2 if on level 1
		if (I.currLevel == LevelEnum::LEVEL1)
		{
			SceneManager::SetNextScene(new SecondScene());
		}
		// change to victory screen if on level 2
		else if (I.currLevel == LevelEnum::LEVEL2)
		{
			I.pHUDManager->Victory();
		}
	}
}

void GameManager::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_N)
	{
		SceneManager::SetNextScene(new SecondScene());
	}
}