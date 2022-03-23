

#ifndef EnemyPlaneSpawner_
#define EnemyPlaneSpawner_

#include "Vect.h"
#include "Matrix.h"
#include "../Gemini Engine/GameObject.h"
#include <stack>
#include <list>

class ToyPlane;
class EnemyPlane;

class EnemyPlaneSpawner : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	EnemyPlaneSpawner() = delete;
	EnemyPlaneSpawner(const EnemyPlaneSpawner&) = delete;
	EnemyPlaneSpawner& operator= (const EnemyPlaneSpawner&) = delete;
	~EnemyPlaneSpawner();

	EnemyPlaneSpawner(ToyPlane* playerPlane);

	virtual void Alarm0();
	void ReturnEnemyPlane(EnemyPlane* e);
	EnemyPlane* GetEnemyPlane();
	void Cleanup();

	using EnemyPlaneDeleteRef = std::list<EnemyPlane*>::iterator;

private:
	static const int SPAWNPOINT_COUNT = 4;
	Vect EnemySpawnPoints[SPAWNPOINT_COUNT];

	std::list<EnemyPlane*> liveEnemyList;
	std::stack<EnemyPlane*> recycledEnemyStack;

	ToyPlane* PlayerPlane;

	int count = 0;
};


#endif EnemyPlaneSpawner_
