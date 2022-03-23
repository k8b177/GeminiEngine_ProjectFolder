#ifndef EnemySpawner_
#define EnemySpawner_

#include "Vect.h"
#include "Matrix.h"
#include "../Gemini Engine/GameObject.h"
#include <stack>
#include <list>

class Enemy;
class Tank;

class EnemySpawner : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	EnemySpawner() = delete;
	EnemySpawner(const EnemySpawner&) = delete;
	EnemySpawner& operator= (const EnemySpawner&) = delete;
	~EnemySpawner() = default;

	EnemySpawner(Tank* playerTank);

	virtual void Alarm0();
	// --- For showing alarm get time and change time
	virtual void KeyPressed(AZUL_KEY k);
	// ---
	void ReturnEnemy(Enemy* e);
	Enemy* GetEnemy();
	void Cleanup();

	using EnemyDeleteRef = std::list<Enemy*>::iterator;

private:
	static const int SPAWNPOINT_COUNT = 4;
	Vect EnemySpawnPoints[SPAWNPOINT_COUNT];

	std::list<Enemy*> liveEnemyList;
	std::stack<Enemy*> recycledEnemyStack;

	Tank* PlayerTank;



	int count = 0;
};


#endif EnemySpawner_
