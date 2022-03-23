#ifndef BombFactory_
#define BombFactory_

#include "Matrix.h"
#include "BombObjectPool.h"

class Bomb;

class BombFactory  // singleton
{
private:
	static BombFactory* ptrInstance;

	BombObjectPool myBombPool;

	static BombFactory& Instance();

	// ---- BIG FOUR ---- //
	BombFactory() {};
	BombFactory(const BombFactory&) = delete;
	BombFactory& operator= (const BombFactory&) = delete;
	~BombFactory() = default;

	Bomb* privCreateBomb(Matrix gunRotPos);
	void privBombReturn(Bomb* b);

public:
	static Bomb* CreateBomb(Matrix gunRotPos) { return Instance().privCreateBomb(gunRotPos); }
	static void BombReturn(Bomb* b) { Instance().privBombReturn(b); }

	static void Delete();
};

#endif BombFactory_
