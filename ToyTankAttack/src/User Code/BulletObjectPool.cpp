#include "BulletObjectPool.h"
#include "Bullet.h"

Bullet* BulletObjectPool::GetBullet()
{
	Bullet* b;

	if (recycledItems.empty())
	{
		b = new Bullet();
	}
	else
	{
		b = recycledItems.top();
		recycledItems.pop();
	}

	BulletListRef ref = liveBullets.insert(liveBullets.end(), b);
	b->SetBulletListRef(ref);

	return b;
}

void BulletObjectPool::ReturnBullet(Bullet* b)
{
	liveBullets.erase(b->GetBulletListRef());
	recycledItems.push(b);
}

BulletObjectPool::~BulletObjectPool()
{
	// forcefully delete all liveBullets (that haven't been recycled yet)
	for (Bullet* b : liveBullets)
	{
		delete b;
	}

	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}