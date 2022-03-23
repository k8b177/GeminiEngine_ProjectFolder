
#ifndef GameManager_
#define GameManager_

#include "../Gemini Engine/GameObject.h"
#include "LevelEnum.h"

class HUDManager;

class GameManager : public GameObject
{
private:
	static GameManager* ptrInstance;

	static GameManager& Instance();

	// ---- BIG FOUR ---- //
	GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator= (const GameManager&) = delete;
	~GameManager();



	void privInitializeLevel(LevelEnum level, HUDManager* p);


	int numEnemiesKilled;
	int numEnemiesToKill;
	LevelEnum currLevel;
	HUDManager* pHUDManager;

public:
	static void Delete();
	static void InitializeLevel(LevelEnum level, HUDManager* p) 
	{ Instance().privInitializeLevel(level, p); }

	static void EnemyKilled();

	static int GetNumEnemiesToKill();
	static int GetNumEnemiesKilled();

	virtual void KeyPressed(AZUL_KEY k);
};

#endif GameManager_