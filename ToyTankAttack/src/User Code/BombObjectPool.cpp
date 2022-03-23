#include "BombObjectPool.h"
#include "Bomb.h"

Bomb* BombObjectPool::GetBomb()
{
	Bomb* b;

	if (recycledItems.empty())
	{
		b = new Bomb();
	}
	else
	{
		b = recycledItems.top();
		recycledItems.pop();
	}

	BombListRef ref = liveBombs.insert(liveBombs.end(), b);
	b->SetBombListRef(ref);

	return b;
}

void BombObjectPool::ReturnBomb(Bomb* b)
{
	liveBombs.erase(b->GetBombListRef());
	recycledItems.push(b);
}

BombObjectPool::~BombObjectPool()
{
	// forcefully delete all liveBombs (that haven't been recycled yet)
	for (Bomb* b : liveBombs)
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