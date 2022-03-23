#ifndef BulletObjectPool_
#define BulletObjectPool_

#include <stack>
#include <list>

class Bullet;

class BulletObjectPool
{
public:
	using BulletList = std::list<Bullet*>;
	using BulletListRef = BulletList::iterator;

private:
	BulletList liveBullets;
	std::stack<Bullet*> recycledItems;

public:
	BulletObjectPool() = default;
	BulletObjectPool(const BulletObjectPool&) = delete;
	BulletObjectPool& operator=(const BulletObjectPool&) = delete;
	~BulletObjectPool();

	Bullet* GetBullet();

	void ReturnBullet(Bullet* b);
};


#endif BulletObjectPool_
