#ifndef BombObjectPool_
#define BombObjectPool_

#include <stack>
#include <list>

class Bomb;

class BombObjectPool
{
public:
	using BombList = std::list<Bomb*>;
	using BombListRef = BombList::iterator;

private:
	BombList liveBombs;
	std::stack<Bomb*> recycledItems;

public:
	BombObjectPool() = default;
	BombObjectPool(const BombObjectPool&) = delete;
	BombObjectPool& operator=(const BombObjectPool&) = delete;
	~BombObjectPool();

	Bomb* GetBomb();

	void ReturnBomb(Bomb* b);
};


#endif BombObjectPool_
