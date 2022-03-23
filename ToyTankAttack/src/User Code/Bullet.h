#ifndef Bullet_
#define Bullet_

#include "../Gemini Engine/GameObject.h"
#include "Matrix.h"
#include "BulletObjectPool.h"

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;
class Enemy;
class Obstacle;
class EnemyPlane;


class Bullet : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	Bullet();
	Bullet(const Bullet&) = delete;
	Bullet& operator= (const Bullet&) = delete;
	~Bullet();

	virtual void Update();
	virtual void Draw();
	virtual void SceneEntry();
	virtual void SceneExit();
	virtual void Alarm0();

	void Collision(Enemy*);
	void Collision(Obstacle*);
	void Collision(EnemyPlane*);

	void Initialize(Matrix shipRotPos);
	void SetBulletListRef(BulletObjectPool::BulletListRef r);
	BulletObjectPool::BulletListRef GetBulletListRef();

private:
	GraphicsObject_WireframeConstantColor* pGObj_BulletWireframe;
	GraphicsObject_TextureLight* pGObj_Bullet;

	Matrix BulletScale;
	Matrix BulletRotTrans;
	float BulletSpeed;

	BulletObjectPool::BulletListRef myBulletListRef;

	bool markedToExitScene;

};


#endif Bullet_
