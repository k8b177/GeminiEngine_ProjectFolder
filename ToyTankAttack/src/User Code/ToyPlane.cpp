#include "ToyPlane.h"

#include "Vect.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include "Keyboard.h"
#include "DebugOut.h"
#include "../Gemini Engine/ModelManager.h"
#include "../Gemini Engine/ShaderManager.h"
#include "../Gemini Engine/TextureManager.h"

#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/Scene.h"

#include "BulletFactory.h"
#include "BombFactory.h"
#include "CameraController.h"
#include "HUDManager.h"


ToyPlane::ToyPlane(HUDManager* hm)
	:pHUD(hm)
{
	// Creating Graphics Object for Ship
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	//Texture* TankBody_TrackTex = TextureManager::Get("TrackTex");
	//Texture* TankBody_BaseTex = TextureManager::Get("BodyTex");
	//Texture* TankBody_WheelsTex = TextureManager::Get("BodyTex");
	//pGObj_Tank = new GraphicsObject_TextureLight(ModelManager::Get("TankBody"), ShaderManager::Get("TextureLight"), TankBody_TrackTex, TankBody_BaseTex, TankBody_WheelsTex, LightColor, LightPos);
	Texture* tex = TextureManager::Get("ToyPlaneTex");
	pGObj = new GraphicsObject_TextureLight(ModelManager::Get("ToyPlane"), ShaderManager::Get("TextureLight"), tex, LightColor, LightPos);

	
	Trans = Matrix(TRANS, 0, 100.0f, 0);
	Scale = Matrix(SCALE, 1, 1, 1);
	Rot = Matrix(ROT_X, 3.14159f * -0.5f);
	RotTrans = Rot * Trans;
	World = Scale * Rot * Trans;
	pGObj->SetWorld(World);

	// Setting up Gun
	GunOffset = Matrix(TRANS, -17.0f, 0.0f, 6.0f);

	SubmitDrawRegistration();
	SubmitUpdateRegistration();
	SubmitCollisionRegistration();
	SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_PRESS);
	SubmitKeyRegistration(AZUL_KEY::KEY_LEFT_SHIFT, EVENT_TYPE::KEY_PRESS);
	SubmitKeyRegistration(AZUL_KEY::KEY_LEFT_SHIFT, EVENT_TYPE::KEY_RELEASE);

	SetColliderModel(pGObj->getModel());
	SetCollidableGroup<ToyPlane>();

	UpdateCollisionData(World);

	health = 1.0f;
	backingUpCounter = 0;
}

void ToyPlane::SetCameraController(CameraController* c)
{
	camController = c;
}

Matrix ToyPlane::GetGunOffset()
{
	return GunOffset;
}

void ToyPlane::Update()
{
	PrevWorld = World;
	PrevRotTrans = RotTrans;
	GunWorldPrev = GunWorld;

	

	// Rotation movement
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A)) // turn left
	{
		RotTrans = Matrix(ROT_Z, ShipRotAng) * RotTrans;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D)) // turn right
	{
		RotTrans = Matrix(ROT_Z, -ShipRotAng) * RotTrans;
	}

	// Back up if at a wall
	if (backingUpCounter > 0)
	{
		backingUpCounter -= 1;
		RotTrans = Matrix(TRANS, Vect(Speed, 0, 0)) * RotTrans;
	}
	else
	{
		RotTrans = Matrix(TRANS, Vect(-Speed, 0, 0)) * RotTrans;
	}
		

	// Plane adjust matrix
	World = Scale * RotTrans;
	pGObj->SetWorld(World);
	UpdateCollisionData(World);

	// Get the Plane's Translation and Rotation Matrices, separated
	Matrix TransTemp = Matrix(TRANS, RotTrans.get(MatrixRowType::ROW_3));
	Matrix RotTemp = Matrix(RotTrans.get(MatrixRowType::ROW_0),
		RotTrans.get(MatrixRowType::ROW_1), RotTrans.get(MatrixRowType::ROW_2),
		Vect(0, 0, 0, 1));

	// Position the Gun
	GunWorld = GunOffset * RotTemp;
	GunWorld = GunWorld * TransTemp;

	GunWorld = Matrix(ROT_Y, 3.14f * -0.5f) * GunWorld;

	CheckBounds();
}

void ToyPlane::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE)
	{
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT))
			BombFactory::CreateBomb(World);
		else
			BulletFactory::CreateBullet(GunWorld);
	}
	else if (k == AZUL_KEY::KEY_LEFT_SHIFT)
	{
		camController->SetCamOffset(Matrix(TRANS, 10.0f, 0.0f, 200.0f));
	}
}

void ToyPlane::KeyReleased(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_LEFT_SHIFT)
	{
		camController->SetCamOffset(Matrix(TRANS, Vect(75.0f, 0.0f, 20.0f)));
	}
}

void ToyPlane::Draw()
{
	pGObj->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

ToyPlane::~ToyPlane()
{
	delete pGObj;
	BulletFactory::Delete();
	BombFactory::Delete();
}

Matrix& ToyPlane::GetPlayerRotTrans()
{
	return RotTrans;
}

Matrix& ToyPlane::GetWorld()
{
	return World;
}

void ToyPlane::UpdateHealth(float h)
{
	health -= h;
	pHUD->UpdateHealth(health);

	if (health <= 0)
	{
		pHUD->GameOver();
	}
}

void ToyPlane::Collision(EnemyPlane*)
{
	UpdateHealth(0.25f);
}

void ToyPlane::CheckBounds()
{
	if (World.M12() < -390.0f || World.M12() > 390.0f || World.M14() < -390.0f || World.M14() > 390.0f)
		backingUpCounter = 60;
}