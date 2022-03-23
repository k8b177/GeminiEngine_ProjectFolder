#include "Enemy.h"

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

#include "EnemyBulletFactory.h"
#include "EnemySpawner.h"
#include "Tank.h"
#include "Bullet.h"

#include "GameManager.h"


Enemy::Enemy(EnemySpawner* p, Tank* playerTank)
	:pEnemySpawner(p), PlayerTank(playerTank)
{
	// Creating Graphics Object for Ship
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Texture* Green = TextureManager::Get("ArmyGreen");
	pGObj_Tank = new GraphicsObject_TextureLight(ModelManager::Get("TankBody"), ShaderManager::Get("TextureLight"), Green, Green, Green, LightColor, LightPos);

	
	pGObj_Turret = new GraphicsObject_TextureLight(ModelManager::Get("TankTurret"), ShaderManager::Get("TextureLight"), Green, Green, Green, LightColor, LightPos);

	SetColliderModel(pGObj_Tank->getModel());
	SetCollidableGroup<Enemy>();
}

void Enemy::Alarm0()
{
	EnemyBulletFactory::CreateBullet(GunWorld);

	SubmitAlarmRegistration(2.0f, AlarmableManager::ALARM_ID::ALARM_0);
}

void Enemy::Alarm1()
{
	Vect playerPos = PlayerTank->GetTankWorld().get(ROW_3);
	Vect enemyPos = TankWorld.get(ROW_3);
	Vect directionToPlayer = (playerPos - enemyPos).norm();


	// get angle between enemy tank and player tank
	Vect a = ForwardVect;
	Vect b = -directionToPlayer;
	float dot = a.dot(b);
	float angle = acos(dot);

	// if player to the right of enemy, need to negate the angle
	Vect cross = a.cross(b);
	if (cross.Y() < 0)
		angle *= -1;


	RotTrans = Matrix(ROT_Y, angle) * RotTrans;

	ForwardVect = -directionToPlayer;

	SubmitAlarmRegistration(2.0f, AlarmableManager::ALARM_ID::ALARM_1);
}

void Enemy::SceneEntry()
{
	backingUpCounter = 0;

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	SubmitAlarmRegistration(0.2f, AlarmableManager::ALARM_ID::ALARM_1);
	SubmitCollisionRegistration();
	SubmitAlarmRegistration(2.0f, AlarmableManager::ALARM_ID::ALARM_0);
}

void Enemy::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_1);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);

	GameManager::EnemyKilled();

	pEnemySpawner->ReturnEnemy(this);
}

void Enemy::Initialize(Vect startingPos)
{
	float scale = 0.25f;

	// Setting Up Tank
	TankScale.set(SCALE, scale, scale, scale);
	TankRot = Matrix(ROT_Y, 3.14f);
	TankTrans = Matrix(TRANS, startingPos);
	RotTrans = TankRot * TankTrans;// rottrans matrix
	Matrix world = TankScale * RotTrans;
	pGObj_Tank->SetWorld(world); // placing ship in the world

	// Setting up Turret
	TurretScale.set(SCALE, scale, scale, scale);
	TurretRot = TankRot;
	TurretYOffset = scale * 12.0f;

	// Setting up Gun
	GunOffset = Matrix(TRANS, 0.0f, scale * 4.4f, scale * 60.0f);

	ForwardVect = Vect(0, 0, 1);

	health = 1;
}

void Enemy::SetDeleteRef(EnemySpawner::EnemyDeleteRef ref)
{
	this->myDeleteRef = ref;
}

EnemySpawner::EnemyDeleteRef Enemy::GetDeleteRef()
{
	return this->myDeleteRef;
}

void Enemy::Update()
{
	TankPrevWorld = TankWorld;
	TankPrevRotTrans = RotTrans;
	TurretPrevWorld = TurretWorld;
	TurretPrevRotTrans = TurretRotTrans;
	TurretPrevRot = TurretRot;
	GunWorldPrev = GunWorld;

	if (backingUpCounter > 0)
	{
		backingUpCounter -= 1;
		RotTrans = Matrix(TRANS, Vect(0, 0, -Speed)) * RotTrans;
	}

	else
	{
		RotTrans = Matrix(TRANS, Vect(0, 0, Speed)) * RotTrans;
	}

	TankWorld = TankScale * RotTrans;
	pGObj_Tank->SetWorld(TankWorld);
	UpdateCollisionData(TankWorld);


	// Position the Turret 
	TurretRotTrans = RotTrans;
	TurretRotTrans *= Matrix(TRANS, 0.0f, TurretYOffset, 0.0f);
	TurretWorld = TurretScale * TurretRotTrans;
	pGObj_Turret->SetWorld(TurretWorld);

	// Get the Turret's Translation and Rotation Matrices, separated
	Matrix TurretTransTemp = Matrix(TRANS, TurretRotTrans.get(MatrixRowType::ROW_3));
	Matrix TurretRotTemp = Matrix(TurretRotTrans.get(MatrixRowType::ROW_0),
		TurretRotTrans.get(MatrixRowType::ROW_1), TurretRotTrans.get(MatrixRowType::ROW_2),
		Vect(0, 0, 0, 1));

	// Position the Gun
	GunWorld = GunOffset * TurretRotTemp;
	GunWorld = GunWorld * TurretTransTemp;
}

void Enemy::Draw()
{
	pGObj_Tank->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	pGObj_Turret->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}


Enemy::~Enemy()
{
	delete pGObj_Turret;
	delete pGObj_Tank;

	EnemyBulletFactory::Delete();
}

void Enemy::Collision(Obstacle*)
{
	backingUpCounter = 100;
}

void Enemy::Collision(Tank*)
{
	backingUpCounter = 20;
}

void Enemy::Collision(Enemy*)
{
	//backingUpCounter = 30;
}

void Enemy::StopMovement()
{
	TankWorld = TankPrevWorld;
	RotTrans = TankPrevRotTrans;
	pGObj_Tank->SetWorld(TankPrevWorld);
	UpdateCollisionData(TankPrevWorld);

	TurretWorld = TurretPrevWorld;
	TurretRotTrans = TurretPrevRotTrans;
	TurretRot = TurretPrevRot;
	pGObj_Turret->SetWorld(TurretPrevWorld);

	GunWorld = GunWorldPrev;
}

void Enemy::Collision(Bullet* b)
{
	assert(b != nullptr);
	health -= 0.5;
	if (health <= 0)
	{
		SubmitExit();
	}
}
