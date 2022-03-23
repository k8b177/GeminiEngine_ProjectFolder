#include "BulletFactory.h"

#include "Bullet.h"

BulletFactory* BulletFactory::ptrInstance = nullptr;

BulletFactory& BulletFactory::Instance()
{
	if (!ptrInstance)
		ptrInstance = new BulletFactory();
	return *ptrInstance;
}

Bullet* BulletFactory::privCreateBullet(Matrix gunRotPos)
{
	Bullet* b;

	// get new or recycled bullet
	b = myBulletPool.GetBullet();

	b->Initialize(gunRotPos);
	b->SubmitEntry();

	return b;
}

void BulletFactory::privBulletReturn(Bullet* b)
{
	myBulletPool.ReturnBullet(b);
}

void BulletFactory::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}