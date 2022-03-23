#ifndef EnemyBulletObjectPool_
#define EnemyBulletObjectPool_

#include <stack>
#include <list>

class EnemyBullet;

class EnemyBulletObjectPool
{
public:
	using BulletList = std::list<EnemyBullet*>;
	using BulletListRef = BulletList::iterator;

private:
	BulletList liveBullets;
	std::stack<EnemyBullet*> recycledItems;

public:
	EnemyBulletObjectPool() = default;
	EnemyBulletObjectPool(const EnemyBulletObjectPool&) = delete;
	EnemyBulletObjectPool& operator=(const EnemyBulletObjectPool&) = delete;
	~EnemyBulletObjectPool();

	EnemyBullet* GetBullet();

	void ReturnBullet(EnemyBullet* b);
};


#endif EnemyBulletObjectPool_
