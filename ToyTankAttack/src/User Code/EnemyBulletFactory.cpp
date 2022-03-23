#include "EnemyBulletFactory.h"

#include "EnemyBullet.h"

EnemyBulletFactory* EnemyBulletFactory::ptrInstance = nullptr;

EnemyBulletFactory& EnemyBulletFactory::Instance()
{
	if (!ptrInstance)
		ptrInstance = new EnemyBulletFactory();
	return *ptrInstance;
}

EnemyBullet* EnemyBulletFactory::privCreateBullet(Matrix gunRotPos)
{
	EnemyBullet* b;

	// get new or recycled bullet
	b = myBulletPool.GetBullet();

	b->Initialize(gunRotPos);
	b->SubmitEntry();

	return b;
}

void EnemyBulletFactory::privBulletReturn(EnemyBullet* b)
{
	myBulletPool.ReturnBullet(b);
}

void EnemyBulletFactory::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}