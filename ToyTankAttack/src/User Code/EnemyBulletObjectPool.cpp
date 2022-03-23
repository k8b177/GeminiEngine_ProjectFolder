#include "EnemyBulletObjectPool.h"
#include "EnemyBullet.h"

EnemyBullet* EnemyBulletObjectPool::GetBullet()
{
	EnemyBullet* b;

	if (recycledItems.empty())
	{
		b = new EnemyBullet();
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

void EnemyBulletObjectPool::ReturnBullet(EnemyBullet* b)
{
	liveBullets.erase(b->GetBulletListRef());
	recycledItems.push(b);
}

EnemyBulletObjectPool::~EnemyBulletObjectPool()
{
	// forcefully delete all liveBullets (that haven't been recycled yet)
	for (EnemyBullet* b : liveBullets)
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