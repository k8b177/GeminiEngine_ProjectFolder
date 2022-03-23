

#ifndef EnemyPlane_
#define EnemyPlane_

#include "../Gemini Engine/GameObject.h"
#include "Matrix.h"
#include "EnemyPlaneSpawner.h"

class GraphicsObject_TextureLight;
class ToyPlane;
class Bullet;

class EnemyPlane : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	EnemyPlane() = default;
	EnemyPlane(const EnemyPlane&) = delete;
	EnemyPlane& operator= (const EnemyPlane&) = delete;
	~EnemyPlane();

	EnemyPlane(EnemyPlaneSpawner* p, ToyPlane* playerPlane);

	// ---- GAME OBJECT METHODS ---- //
	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	virtual void SceneExit();
	virtual void SceneEntry();

	//virtual void KeyPressed(AZUL_KEY k);

	void Initialize(Vect startingPos);
	void SetDeleteRef(EnemyPlaneSpawner::EnemyPlaneDeleteRef ref);
	EnemyPlaneSpawner::EnemyPlaneDeleteRef GetDeleteRef();


	// ---- COLLISION ---- //
	void Collision(ToyPlane*);
	void Collision(Bullet*);

private:
	GraphicsObject_TextureLight* pGObj;

	float Angle;
	Matrix Origin;

	Matrix Scale;
	Matrix RotTrans;
	Matrix Rot;
	Matrix Trans;
	Matrix World;
	Matrix PrevWorld;
	Matrix PrevRotTrans;


	Matrix GunRotTrans;
	Matrix GunOffset;
	Matrix GunTrans;
	Matrix GunWorld;
	Matrix GunWorldPrev;

	Vect MovementDirection;
	Vect ForwardVect;


	const float Speed = 0.75f;
	const float ShipRotAng = .05f;

	EnemyPlaneSpawner* pEnemySpawner;
	EnemyPlaneSpawner::EnemyPlaneDeleteRef myDeleteRef;

	ToyPlane* PlayerPlane;

};


#endif EnemyPlane_
