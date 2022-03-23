


#include "EnemyPlane.h"

#include "Vect.h"
#include "GraphicsObject_TextureLight.h"
#include "DebugOut.h"
#include "../Gemini Engine/ModelManager.h"
#include "../Gemini Engine/ShaderManager.h"
#include "../Gemini Engine/TextureManager.h"

#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/Scene.h"

#include "EnemyPlaneSpawner.h"
#include "ToyPlane.h"

#include "GameManager.h"


EnemyPlane::EnemyPlane(EnemyPlaneSpawner* p, ToyPlane* playerPlane)
	:pEnemySpawner(p), PlayerPlane(playerPlane)
{
	// Creating Graphics Object
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Texture* tex = TextureManager::Get("ToyPlaneTex");
	pGObj = new GraphicsObject_TextureLight(ModelManager::Get("ToyPlane"), ShaderManager::Get("TextureLight"), tex, LightColor, LightPos);

	Scale = Matrix(SCALE, 1, 1, 1);

	// Setting up Gun
	GunOffset = Matrix(TRANS, -17.0f, 0.0f, 6.0f);

	SetColliderModel(pGObj->getModel());
	SetCollidableGroup<EnemyPlane>();
}




void EnemyPlane::SceneEntry()
{
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	SubmitAlarmRegistration(0.2f, AlarmableManager::ALARM_ID::ALARM_0);
	SubmitCollisionRegistration();
}

void EnemyPlane::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);


	pEnemySpawner->ReturnEnemyPlane(this);
}

void EnemyPlane::Initialize(Vect startingPos)
{
	float scale = 1.0f;

	// Setting Up Tank
	//TankScale.set(SCALE, 25.0f, 15.0f, 40.0f); // scale matrix
	Scale.set(SCALE, scale, scale, scale);
	Rot = Matrix(ROT_X, 3.14159f * -0.5f) * Matrix(ROT_Y, 3.15159f * -0.5f);
	Trans = Matrix(TRANS, startingPos);
	RotTrans = Rot * Trans;// rottrans matrix
	World = Scale * RotTrans;
	pGObj->SetWorld(World); // placing ship in the world

	ForwardVect = Vect(0, 0, 1);
	Angle = 0.0f;
}

void EnemyPlane::SetDeleteRef(EnemyPlaneSpawner::EnemyPlaneDeleteRef ref)
{
	this->myDeleteRef = ref;
}

EnemyPlaneSpawner::EnemyPlaneDeleteRef EnemyPlane::GetDeleteRef()
{
	return this->myDeleteRef;
}

void EnemyPlane::Update()
{
	RotTrans = Matrix(TRANS, Vect(-Speed, 0, 0)) * RotTrans;

	World = Scale * RotTrans;
	pGObj->SetWorld(World);
	UpdateCollisionData(World);
}

void EnemyPlane::Draw()
{
	pGObj->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	pGObj->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void EnemyPlane::Alarm0()
{
	Vect playerPos = PlayerPlane->GetWorld().get(ROW_3);
	Vect enemyPos = World.get(ROW_3);
	Vect directionToPlayer = (playerPos - enemyPos).norm();


	// get angle between enemy and player 
	Vect a = ForwardVect;
	Vect b = -directionToPlayer;
	float dot = a.dot(b);
	float angle = acos(dot);

	// if player to the right of enemy, need to negate the angle
	Vect cross = a.cross(b);
	if (cross.Y() < 0)
		angle *= -1;


	RotTrans = Matrix(ROT_Z, angle) * RotTrans;

	ForwardVect = -directionToPlayer;

	SubmitAlarmRegistration(1.0f, AlarmableManager::ALARM_ID::ALARM_0);
}


EnemyPlane::~EnemyPlane()
{
	delete pGObj;
}

void EnemyPlane::Collision(ToyPlane*)
{
	SubmitExit();
}

void EnemyPlane::Collision(Bullet*)
{
	SubmitExit();
}
