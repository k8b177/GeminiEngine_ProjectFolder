#include "Bullet.h"

#include "GraphicsObject_WireframeConstantColor.h"
#include "GraphicsObject_TextureLight.h"
#include "../Gemini Engine/ModelManager.h"
#include "../Gemini Engine/ShaderManager.h"
#include "../Gemini Engine/TextureManager.h"
#include "../Gemini Engine/CameraManager.h"

#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/Scene.h"

#include "BulletFactory.h"

Bullet::Bullet()
{
	// Creating Graphics Object for Bullet
	// Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	// pGObj_BulletWireframe = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ColorConstant"), Blue);

	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Texture* pBulletTex = TextureManager::Get("BulletTex");
	pGObj_Bullet = new GraphicsObject_TextureLight(ModelManager::Get("Bullet"), ShaderManager::Get("TextureLight"), pBulletTex, pBulletTex, LightColor, LightPos);

	float scale = 0.08f;
	BulletScale.set(SCALE, scale, scale, scale);

	BulletSpeed = 4.0f;

	SetColliderModel(pGObj_Bullet->getModel());
	SetCollidableGroup<Bullet>();
}

void Bullet::Initialize(Matrix shipRotPos)
{
	BulletRotTrans = shipRotPos;
}

void Bullet::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitAlarmRegistration(3.0f, AlarmableManager::ALARM_ID::ALARM_0);
	SubmitCollisionRegistration();

	markedToExitScene = false;
}

void Bullet::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();
	
	BulletFactory::BulletReturn(this);
}

void Bullet::Update()
{
	BulletRotTrans = Matrix(TRANS, Vect(0, 0, BulletSpeed)) * BulletRotTrans;

	// Spaceship adjust matrix
	Matrix world = BulletScale * BulletRotTrans;
	//pGObj_BulletWireframe->SetWorld(world);
	pGObj_Bullet->SetWorld(world);
	UpdateCollisionData(world);
}

void Bullet::Draw()
{
	// pGObj_BulletWireframe->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	pGObj_Bullet->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Bullet::Alarm0()
{
	SubmitExit();
}


Bullet::~Bullet()
{
	// delete pGObj_BulletWireframe;
	delete pGObj_Bullet;
}

void Bullet::SetBulletListRef(BulletObjectPool::BulletListRef r)
{
	this->myBulletListRef = r;
}

BulletObjectPool::BulletListRef Bullet::GetBulletListRef()
{
	return this->myBulletListRef;
}

void Bullet::Collision(Enemy*)
{
	if (!markedToExitScene)
	{
		SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);

		SubmitExit();
		markedToExitScene = true;
	}
}

void Bullet::Collision(Obstacle*)
{
	if (!markedToExitScene)
	{
		SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);

		SubmitExit();
		markedToExitScene = true;
	}
}

void Bullet::Collision(EnemyPlane*)
{
	if (!markedToExitScene)
	{
		SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);

		SubmitExit();
		markedToExitScene = true;
	}
}