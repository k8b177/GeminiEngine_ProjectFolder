#ifndef ToyPlane_
#define ToyPlane_

#include "Player.h"

#include "Matrix.h"

#include "DebugOut.h"

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;
class EnemyPlane;
class CameraController;
class HUDManager;

class ToyPlane : public Player
{
public:
	// ---- BIG FOUR ---- //
	ToyPlane() = delete;
	ToyPlane(const ToyPlane&) = delete;
	ToyPlane& operator= (const ToyPlane&) = delete;
	~ToyPlane();

	ToyPlane(HUDManager* hm);

	// ---- GAME OBJECT METHODS ---- //
	virtual void Update();
	virtual void Draw();
	virtual void KeyPressed(AZUL_KEY k);
	virtual void KeyReleased(AZUL_KEY k);

	Matrix& GetPlayerRotTrans();
	Matrix GetGunOffset();

	void Collision(EnemyPlane*);

	void SetCameraController(CameraController* c);
	Matrix& GetWorld();


private:
	void UpdateHealth(float h);
	void CheckBounds();


	GraphicsObject_TextureLight* pGObj;

	CameraController* camController;
	HUDManager* pHUD;

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


	const float Speed = 1.0f;
	const float ShipRotAng = .025f;


	float health;

	int backingUpCounter;

};


#endif ToyPlane_
