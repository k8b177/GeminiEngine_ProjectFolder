#ifndef Tank_
#define Tank_

#include "Player.h"
#include "Matrix.h"

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;
class CameraController;
class Obstacle;
class Enemy;
class EnemyBullet;
class HUDManager;

class Tank : public Player
{
public:
	// ---- BIG FOUR ---- //
	Tank() = delete;
	Tank(const Tank&) = delete;
	Tank& operator= (const Tank&) = delete;
	~Tank();

	Tank(HUDManager* hm);

	// ---- GAME OBJECT METHODS ---- //
	virtual void Update();
	virtual void Draw();
	virtual void KeyPressed(AZUL_KEY k);
	virtual void Alarm0();

	// ---- COLLISION ---- //
	void Collision(Obstacle*);
	void Collision(Enemy*);
	void Collision(EnemyBullet*);


	// ---- MY METHODS ---- //
	//Matrix& GetTurretRotTrans();
	Matrix& GetPlayerRotTrans();
	void StopMovement();
	Matrix& GetTankWorld();
	void CheckBounds();

	

private:
	HUDManager* pHUD;

	GraphicsObject_TextureLight* pGObj_Tank;
	GraphicsObject_WireframeConstantColor* pGObj_TankWireframe;
	GraphicsObject_WireframeConstantColor* pGObj_BSphere;
	GraphicsObject_TextureLight* pGObj_Turret;
	GraphicsObject_WireframeConstantColor* pGObj_GunSphere;

	Matrix TankScale;
	Matrix TankRotTrans;
	Matrix TankRot;
	Matrix TankTrans;
	Matrix TankWorld;
	Matrix TankPrevWorld;
	Matrix TankPrevRotTrans;

	Matrix TurretScale;
	Matrix TurretRot;
	Matrix TurretRotTrans;
	Matrix TurretWorld;
	Matrix TurretOffset;
	float TurretYOffset;
	Matrix TurretPrevWorld;
	Matrix TurretPrevRotTrans;
	Matrix TurretPrevRot;

	Matrix TurretTransTemp;
	Matrix TurretRotTemp;

	Matrix GunRotTrans;
	Matrix GunOffset;
	Matrix GunTrans;
	Matrix GunWorld;
	Matrix GunWorldPrev;


	const float ShipTransSpeed = 1;
	const float ShipRotAng = .05f;
	bool BsphereToggle = false;
	const float startingHealth = 1.0f;

	float health = startingHealth;

	void UpdateHealth(float h);


	CameraController* pCameraController;


};


#endif Tank_
