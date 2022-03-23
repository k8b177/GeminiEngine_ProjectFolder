#include "EnemySpawner.h"

#include "Enemy.h"

#include "DebugOut.h"

#include "../Gemini Engine/ScreenLog.h"

EnemySpawner::EnemySpawner(Tank* playerTank)
	:PlayerTank(playerTank)
{
	EnemySpawnPoints[0] = Vect(200, 0, 200);
	EnemySpawnPoints[1] = Vect(-200, 0, 200);
	EnemySpawnPoints[2] = Vect(200, 0, -200);
	EnemySpawnPoints[3] = Vect(-200, 0, -200);

	SubmitAlarmRegistration(5.0f, AlarmableManager::ALARM_ID::ALARM_0);
	count = 0;

	// For Demonstrating changing alarm time
	SubmitKeyRegistration(AZUL_KEY::KEY_RIGHT_BRACKET, EVENT_TYPE::KEY_PRESS);
	SubmitKeyRegistration(AZUL_KEY::KEY_LEFT_BRACKET, EVENT_TYPE::KEY_PRESS);
	SubmitKeyRegistration(AZUL_KEY::KEY_0, EVENT_TYPE::KEY_PRESS);
	SubmitKeyRegistration(AZUL_KEY::KEY_MINUS, EVENT_TYPE::KEY_PRESS);
}

void EnemySpawner::Alarm0()
{
	if (liveEnemyList.size() < SPAWNPOINT_COUNT)
	{
		Enemy* e = GetEnemy();
		e->Initialize(EnemySpawnPoints[count]);
		e->SubmitEntry();

		count++;
		if (count >= SPAWNPOINT_COUNT)
			count = 0;

		EnemyDeleteRef ref = liveEnemyList.insert(liveEnemyList.end(), e);
		e->SetDeleteRef(ref);
	}

	SubmitAlarmRegistration(5.0f, AlarmableManager::ALARM_ID::ALARM_0);
}

void EnemySpawner::ReturnEnemy(Enemy* e)
{
	liveEnemyList.erase(e->GetDeleteRef());
	recycledEnemyStack.push(e);
}

Enemy* EnemySpawner::GetEnemy()
{
	Enemy* e;
	if (recycledEnemyStack.empty())
	{
		e = new Enemy(this, PlayerTank);
	}
	else
	{
		e = recycledEnemyStack.top();
		recycledEnemyStack.pop();
	}
	return e;
}

void EnemySpawner::Cleanup()
{
	// forcefully delete all liveBullets (that haven't been recycled yet)
	for (Enemy* e : liveEnemyList)
	{
		delete e;
	}
	while (!recycledEnemyStack.empty())
	{
		delete recycledEnemyStack.top();
		recycledEnemyStack.pop();
	}
}

void EnemySpawner::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_0:
		DebugMsg::out("Time Left: %f\n", GetAlarmTime(AlarmableManager::ALARM_ID::ALARM_0));
		break;
	case AZUL_KEY::KEY_LEFT_BRACKET:
		SetAlarmTime(-2.0f, AlarmableManager::ALARM_ID::ALARM_0);
		DebugMsg::out("Time Left: %f\n", GetAlarmTime(AlarmableManager::ALARM_ID::ALARM_0));
		break;
	case AZUL_KEY::KEY_RIGHT_BRACKET:
		SetAlarmTime(+7.0f, AlarmableManager::ALARM_ID::ALARM_0);
		DebugMsg::out("Time Left: %f\n", GetAlarmTime(AlarmableManager::ALARM_ID::ALARM_0));
		break;
	case AZUL_KEY::KEY_MINUS:
		SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
		DebugMsg::out("ALARM CANCELLED\n");
		break;
	}
}