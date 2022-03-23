#ifndef BulletFactory_
#define BulletFactory_

#include "Matrix.h"
#include "BulletObjectPool.h"

class Bullet;

class BulletFactory  // singleton
{
private:
	static BulletFactory* ptrInstance;

	BulletObjectPool myBulletPool;

	static BulletFactory& Instance();

	// ---- BIG FOUR ---- //
	BulletFactory() {};
	BulletFactory(const BulletFactory&) = delete;
	BulletFactory& operator= (const BulletFactory&) = delete;
	~BulletFactory() = default;

	Bullet* privCreateBullet(Matrix gunRotPos);
	void privBulletReturn(Bullet* b);

public:
	static Bullet* CreateBullet(Matrix gunRotPos) { return Instance().privCreateBullet(gunRotPos); }
	static void BulletReturn(Bullet* b) { Instance().privBulletReturn(b); }

	static void Delete();
};

#endif BulletFactory_
