#ifndef Enemy_
#define Enemy_

#include "../Gemini Engine/GameObject.h"
#include "Matrix.h"
#include "EnemySpawner.h"

class GraphicsObject_TextureLight;
class TeddyBear;
class LegoBrick;
class Tank;
class Bullet;
class Obstacle;

class Enemy : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	Enemy() = default;
	Enemy(const Enemy&) = delete;
	Enemy& operator= (const Enemy&) = delete;
	~Enemy();

	Enemy(EnemySpawner* p, Tank* playerTank);

	// ---- GAME OBJECT METHODS ---- //
	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	virtual void Alarm1();
	virtual void SceneExit();
	virtual void SceneEntry();

	void Initialize(Vect startingPos);
	void SetDeleteRef(EnemySpawner::EnemyDeleteRef ref);
	EnemySpawner::EnemyDeleteRef GetDeleteRef();


	// ---- MY METHODS ---- //
	void StopMovement();
	void BackUp();

	// ---- COLLISION ---- //
	//void Collision(TeddyBear*);
	//void Collision(LegoBrick*);
	void Collision(Tank*);
	void Collision(Bullet*);
	void Collision(Enemy*);
	void Collision(Obstacle*);

private:
	GraphicsObject_TextureLight* pGObj_Tank;

	GraphicsObject_TextureLight* pGObj_Turret;

	Matrix TankScale;
	Matrix RotTrans;
	Matrix TankRot;
	Matrix TankTrans;
	Matrix TankWorld;
	Matrix TankPrevWorld;
	Matrix TankPrevRotTrans;

	Matrix TurretScale;
	Matrix TurretRot;
	Matrix TurretRotTrans;
	Matrix TurretWorld;
	float TurretYOffset;
	Matrix TurretPrevWorld;
	Matrix TurretPrevRotTrans;
	Matrix TurretPrevRot;

	Matrix GunRotTrans;
	Matrix GunOffset;
	Matrix GunTrans;
	Matrix GunWorld;
	Matrix GunWorldPrev;

	Vect MovementDirection;
	Vect ForwardVect;


	const float Speed = 0.5f;
	const float ShipRotAng = .05f;

	EnemySpawner* pEnemySpawner;
	EnemySpawner::EnemyDeleteRef myDeleteRef;

	Tank* PlayerTank;

	float health;

	int backingUpCounter;

};


#endif Enemy_
