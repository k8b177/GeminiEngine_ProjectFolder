#ifndef EnemyBullet_
#define EnemyBullet_

#include "../Gemini Engine/GameObject.h"
#include "Matrix.h"
#include "EnemyBulletObjectPool.h"

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;
class Tank;
class Obstacle;

class EnemyBullet : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	EnemyBullet();
	EnemyBullet(const EnemyBullet&) = delete;
	EnemyBullet& operator= (const EnemyBullet&) = delete;
	~EnemyBullet();

	virtual void Update();
	virtual void Draw();
	virtual void SceneEntry();
	virtual void SceneExit();
	virtual void Alarm0();

	void Collision(Tank*);
	void Collision(Obstacle*);

	void Initialize(Matrix shipRotPos);
	void SetBulletListRef(EnemyBulletObjectPool::BulletListRef r);
	EnemyBulletObjectPool::BulletListRef GetBulletListRef();

private:
	GraphicsObject_WireframeConstantColor* pGObj_BulletWireframe;
	GraphicsObject_TextureLight* pGObj_Bullet;

	Matrix BulletScale;
	Matrix BulletRotTrans;
	float BulletSpeed;

	EnemyBulletObjectPool::BulletListRef myBulletListRef;

	bool markedToExitScene;


};


#endif EnemyBullet_
