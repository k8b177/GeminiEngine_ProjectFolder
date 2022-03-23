#include "BombFactory.h"

#include "Bomb.h"

BombFactory* BombFactory::ptrInstance = nullptr;

BombFactory& BombFactory::Instance()
{
	if (!ptrInstance)
		ptrInstance = new BombFactory();
	return *ptrInstance;
}

Bomb* BombFactory::privCreateBomb(Matrix gunRotPos)
{
	Bomb* b;

	// get new or recycled bullet
	b = myBombPool.GetBomb();

	b->Initialize(gunRotPos);
	b->SubmitEntry();

	return b;
}

void BombFactory::privBombReturn(Bomb* b)
{
	myBombPool.ReturnBomb(b);
}

void BombFactory::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}