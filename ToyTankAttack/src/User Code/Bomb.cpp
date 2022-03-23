#include "Bomb.h"

#include "GraphicsObject_WireframeConstantColor.h"
#include "GraphicsObject_TextureLight.h"
#include "../Gemini Engine/ModelManager.h"
#include "../Gemini Engine/ShaderManager.h"
#include "../Gemini Engine/TextureManager.h"
#include "../Gemini Engine/CameraManager.h"

#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/Scene.h"

#include "BombFactory.h"

Bomb::Bomb()
{
	// Creating Graphics Object for Bullet
	// Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	// pGObj_BulletWireframe = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ColorConstant"), Blue);

	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Texture* tex = TextureManager::Get("Red");
	pGObj_Bomb = new GraphicsObject_TextureLight(ModelManager::Get("Bomb"), ShaderManager::Get("TextureLight"), tex, LightColor, LightPos);

	float scale = 3.0f;
	BombScale.set(SCALE, scale, scale, scale);

	BombSpeed = 0.75f;

	SetColliderModel(pGObj_Bomb->getModel());
	SetCollidableGroup<Bomb>();
}

void Bomb::Initialize(Matrix shipRotPos)
{
	BombRotTrans = shipRotPos;
}

void Bomb::SceneEntry()
{
	SubmitUpdateRegistration();
	SubmitDrawRegistration();
	SubmitAlarmRegistration(10.0f, AlarmableManager::ALARM_ID::ALARM_0);
	SubmitCollisionRegistration();

	markedToExitScene = false;
}

void Bomb::SceneExit()
{
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();
	SubmitCollisionDeregistration();

	BombFactory::BombReturn(this);
}

void Bomb::Update()
{
	BombRotTrans = Matrix(TRANS, Vect(0, 0, -BombSpeed)) * BombRotTrans;

	// Spaceship adjust matrix
	Matrix world = BombScale * BombRotTrans;
	//pGObj_BulletWireframe->SetWorld(world);
	pGObj_Bomb->SetWorld(world);
	UpdateCollisionData(world);
}

void Bomb::Draw()
{
	// pGObj_BulletWireframe->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	pGObj_Bomb->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Bomb::Alarm0()
{
	SubmitExit();
}


Bomb::~Bomb()
{
	// delete pGObj_BulletWireframe;
	delete pGObj_Bomb;
}

void Bomb::SetBombListRef(BombObjectPool::BombListRef r)
{
	this->myBombListRef = r;
}

BombObjectPool::BombListRef Bomb::GetBombListRef()
{
	return this->myBombListRef;
}

void Bomb::Collision(TeddyBear*)
{
	if (!markedToExitScene)
	{
		SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);

		SubmitExit();
		markedToExitScene = true;
	}
}