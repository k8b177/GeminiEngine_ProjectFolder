#ifndef EnemyBulletFactory_
#define EnemyBulletFactory_

#include "Matrix.h"
#include "EnemyBulletObjectPool.h"

class EnemyBullet;

class EnemyBulletFactory  // singleton
{
private:
	static EnemyBulletFactory* ptrInstance;

	EnemyBulletObjectPool myBulletPool;

	static EnemyBulletFactory& Instance();

	// ---- BIG FOUR ---- //
	EnemyBulletFactory() {};
	EnemyBulletFactory(const EnemyBulletFactory&) = delete;
	EnemyBulletFactory& operator= (const EnemyBulletFactory&) = delete;
	~EnemyBulletFactory() = default;

	EnemyBullet* privCreateBullet(Matrix gunRotPos);
	void privBulletReturn(EnemyBullet* b);

public:
	static EnemyBullet* CreateBullet(Matrix gunRotPos) { return Instance().privCreateBullet(gunRotPos); }
	static void BulletReturn(EnemyBullet* b) { Instance().privBulletReturn(b); }

	static void Delete();
};

#endif EnemyBulletFactory_
