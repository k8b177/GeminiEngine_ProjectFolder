#include "Tank.h"

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
#include "HUDManager.h"

#include "../Gemini Engine/Visualizer.h"
#include "../Gemini Engine/Colors.h"


Tank::Tank(HUDManager* hm)
	:pHUD(hm)
{
	// Creating Graphics Object for Ship
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	//Texture* TankBody_TrackTex = TextureManager::Get("TrackTex");
	//Texture* TankBody_BaseTex = TextureManager::Get("BodyTex");
	//Texture* TankBody_WheelsTex = TextureManager::Get("BodyTex");
	//pGObj_Tank = new GraphicsObject_TextureLight(ModelManager::Get("TankBody"), ShaderManager::Get("TextureLight"), TankBody_TrackTex, TankBody_BaseTex, TankBody_WheelsTex, LightColor, LightPos);
	Texture* Green = TextureManager::Get("ArmyGreen");
	pGObj_Tank = new GraphicsObject_TextureLight(ModelManager::Get("TankBody"), ShaderManager::Get("TextureLight"), Green, Green, Green, LightColor, LightPos);


	//Texture* Turret_BaseTex = TextureManager::Get("BodyTex");
	//Texture* Turret_SecondaryTex = TextureManager::Get("BodyTex");
	//Texture* Turret_ThirdTex = TextureManager::Get("BodyTex");
	//pGObj_Turret = new GraphicsObject_TextureLight(ModelManager::Get("TankTurret"), ShaderManager::Get("TextureLight"), Turret_BaseTex, Turret_SecondaryTex, Turret_ThirdTex, LightColor, LightPos);
	pGObj_Turret = new GraphicsObject_TextureLight(ModelManager::Get("TankTurret"), ShaderManager::Get("TextureLight"), Green, Green, Green, LightColor, LightPos);

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	pGObj_GunSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ColorConstant"), Blue);

	float scale = 0.25f;

	// Setting Up Tank
	TankScale.set(SCALE, scale, scale, scale);
	TankRot = Matrix(ROT_Y, 3.14159f * 0.25f);
	TankTrans = Matrix(TRANS, -350, 0, -350);
	TankRotTrans = TankRot * TankTrans;// rottrans matrix
	Matrix world = TankScale * TankRotTrans;
	pGObj_Tank->SetWorld(world); // placing ship in the world

	// Setting up Turret
	TurretScale = Matrix(SCALE, scale, scale, scale);
	TurretRot = TankRot;
	TurretRotTrans = TurretRot * TankTrans;
	TurretOffset = Matrix(TRANS, 0.0f, scale * 12.0f, 0.0f);


	// Setting up Gun
	GunOffset = Matrix(TRANS, 0.0f, scale * 4.4f, scale * 60.0f);

	// Initializing HUD health
	pHUD->UpdateHealth(startingHealth);

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();


	SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EVENT_TYPE::KEY_PRESS);

	SetColliderModel(pGObj_Tank->getModel());
	SetCollidableGroup<Tank>();
	SubmitCollisionRegistration();
}

void Tank::Update()
{
	//Visualizer::SubmitBSphereVisualization(GetBSphere(), Colors::Blue);

	TankPrevWorld = TankWorld;
	TankPrevRotTrans = TankRotTrans;
	TurretPrevWorld = TurretWorld;
	TurretPrevRotTrans = TurretRotTrans;
	TurretPrevRot = TurretRot;
	GunWorldPrev = GunWorld;


	// Tank Rotation movement
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A)) // turn left
	{
		TankRotTrans = Matrix(ROT_Y, ShipRotAng) * TankRotTrans;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D)) // turn right
	{
		TankRotTrans = Matrix(ROT_Y, -ShipRotAng) * TankRotTrans;
	}

	// Tank translation movement
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W)) // go forward
	{
		TankRotTrans = Matrix(TRANS, Vect(0, 0, ShipTransSpeed)) * TankRotTrans;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S)) // go backward
	{
		TankRotTrans = Matrix(TRANS, Vect(0, 0, -ShipTransSpeed)) * TankRotTrans;
	}


	Matrix TankTransTest = Matrix(TRANS, TankRotTrans.get(MatrixRowType::ROW_3));
	Matrix TankRotTest = Matrix(TankRotTrans.get(MatrixRowType::ROW_0),
		TankRotTrans.get(MatrixRowType::ROW_1), TankRotTrans.get(MatrixRowType::ROW_2),
		Vect(0.0f, 0.0f, 0.0f, 1.0f));

	// Tank adjust matrix
	TankWorld = TankScale * TankRotTrans;
	// pGObj_TankWireframe->SetWorld(TankWorld);
	pGObj_Tank->SetWorld(TankWorld);
	UpdateCollisionData(TankWorld);


	// Turret Rotation movement
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_J)) // rotate left
	{
		TurretRot = Matrix(ROT_Y, ShipRotAng) * TurretRot;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_L)) // rotate right
	{
		TurretRot = Matrix(ROT_Y, -ShipRotAng) * TurretRot;
	}
	/*
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_I)) // rotate up
	{
		TurretRot = Matrix(ROT_X, ShipRotAng) * TurretRot;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K)) // rotate down
	{
		TurretRot = Matrix(ROT_X, -ShipRotAng) * TurretRot;
	}
	*/
	
	// Position the Turret 
	// turret rotation and tank rotation independent
	TurretRotTrans = TurretRot * Matrix(TRANS, TankRotTrans.get(ROW_3)); 
	// turret rotation and tank rotation dependent
	// TurretRotTrans = TurretRot * TankRotTrans;
	TurretRotTrans *= TurretOffset;

	TurretWorld = TurretScale * TurretRotTrans;
	pGObj_Turret->SetWorld(TurretWorld);

	
	// Get the Turret's Translation and Rotation Matrices, separated
	TurretTransTemp = Matrix(TRANS, TurretRotTrans.get(MatrixRowType::ROW_3));
	TurretRotTemp = Matrix(TurretRotTrans.get(MatrixRowType::ROW_0),
		TurretRotTrans.get(MatrixRowType::ROW_1), TurretRotTrans.get(MatrixRowType::ROW_2),
		Vect(0, 0, 0, 1));

	// Position the Gun
	GunWorld = GunOffset * TurretRotTemp;
	GunWorld = GunWorld * TurretTransTemp;


	pGObj_GunSphere->SetWorld(GunWorld);

	CheckBounds();

}

void Tank::Draw()
{
	pGObj_Tank->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	pGObj_Turret->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	//pGObj_GunSphere->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Tank::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE)
	{
		BulletFactory::CreateBullet(GunWorld);
	}
}

Tank::~Tank()
{
	delete pGObj_Turret;
	delete pGObj_Tank;
	delete pGObj_GunSphere;

	BulletFactory::Delete();
}

Matrix& Tank::GetPlayerRotTrans()
{
	return TurretRotTrans;
}

Matrix& Tank::GetTankWorld()
{
	return TankWorld;
}

void Tank::Collision(Obstacle*)
{
	StopMovement();
}

void Tank::Collision(Enemy*)
{
	//UpdateHealth(0.05f);
}

void Tank::CheckBounds()
{
	if (TankWorld.M12() < -390.0f || TankWorld.M12() > 390.0f || TankWorld.M14() < -390.0f || TankWorld.M14() > 390.0f)
		StopMovement();
}

void Tank::StopMovement()
{
	TankWorld = TankPrevWorld;
	TankRotTrans = TankPrevRotTrans;
	pGObj_Tank->SetWorld(TankPrevWorld);
	UpdateCollisionData(TankPrevWorld);

	TurretWorld = TurretPrevWorld;
	TurretRotTrans = TurretPrevRotTrans;
	TurretRot = TurretPrevRot;
	pGObj_Turret->SetWorld(TurretPrevWorld);

	GunWorld = GunWorldPrev;
	pGObj_GunSphere->SetWorld(GunWorldPrev);
}

void Tank::Alarm0()
{
	//pGObj_Tank->pLightColor = new Vect(1.50f, 1.50f, 1.50f, 1.50f);
}

void Tank::Collision(EnemyBullet*)
{
	UpdateHealth(0.1f);
}

void Tank::UpdateHealth(float h)
{
	health -= h;
	pHUD->UpdateHealth(health);
	if (health <= 0)
	{
		pHUD->GameOver();
	}
}
