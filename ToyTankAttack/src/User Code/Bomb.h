#ifndef Bomb_
#define Bomb_

#include "../Gemini Engine/GameObject.h"
#include "Matrix.h"
#include "BombObjectPool.h"

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;
class TeddyBear;

class Bomb : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	Bomb();
	Bomb(const Bomb&) = delete;
	Bomb& operator= (const Bomb&) = delete;
	~Bomb();

	virtual void Update();
	virtual void Draw();
	virtual void SceneEntry();
	virtual void SceneExit();
	virtual void Alarm0();

	void Collision(TeddyBear*);

	void Initialize(Matrix shipRotPos);
	void SetBombListRef(BombObjectPool::BombListRef r);
	BombObjectPool::BombListRef GetBombListRef();

private:
	GraphicsObject_WireframeConstantColor* pGObj_BulletWireframe;
	GraphicsObject_TextureLight* pGObj_Bomb;

	Matrix BombScale;
	Matrix BombRotTrans;
	float BombSpeed;

	BombObjectPool::BombListRef myBombListRef;

	bool markedToExitScene;

};


#endif Bomb_
