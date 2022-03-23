


#include "EnemyPlaneSpawner.h"

#include "EnemyPlane.h"

EnemyPlaneSpawner::EnemyPlaneSpawner(ToyPlane* playerPlane)
	:PlayerPlane(playerPlane)
{
	EnemySpawnPoints[0] = Vect(350, 100, 350);
	EnemySpawnPoints[1] = Vect(-350, 100, 350);
	EnemySpawnPoints[2] = Vect(350, 100, -350);
	EnemySpawnPoints[3] = Vect(-350, 100, -350);

	SubmitAlarmRegistration(2.0f, AlarmableManager::ALARM_ID::ALARM_0);
	count = 0;
}

void EnemyPlaneSpawner::Alarm0()
{
	if (liveEnemyList.size() < SPAWNPOINT_COUNT)
	{
		EnemyPlane* e = GetEnemyPlane();
		e->Initialize(EnemySpawnPoints[count]);
		e->SubmitEntry();

		count++;
		if (count >= SPAWNPOINT_COUNT)
			count = 0;

		EnemyPlaneDeleteRef ref = liveEnemyList.insert(liveEnemyList.end(), e);
		e->SetDeleteRef(ref);
	}

	SubmitAlarmRegistration(2.0f, AlarmableManager::ALARM_ID::ALARM_0);
}

void EnemyPlaneSpawner::ReturnEnemyPlane(EnemyPlane* e)
{
	liveEnemyList.erase(e->GetDeleteRef());
	recycledEnemyStack.push(e);
}

EnemyPlane* EnemyPlaneSpawner::GetEnemyPlane()
{
	EnemyPlane* e;
	if (recycledEnemyStack.empty())
	{
		e = new EnemyPlane(this, PlayerPlane);
	}
	else
	{
		e = recycledEnemyStack.top();
		recycledEnemyStack.pop();
	}
	return e;
}

void EnemyPlaneSpawner::Cleanup()
{
	// forcefully delete all liveBullets (that haven't been recycled yet)
	for (EnemyPlane* e : liveEnemyList)
	{
		delete e;
	}
	while (!recycledEnemyStack.empty())
	{
		delete recycledEnemyStack.top();
		recycledEnemyStack.pop();
	}
}

EnemyPlaneSpawner::~EnemyPlaneSpawner()
{

}