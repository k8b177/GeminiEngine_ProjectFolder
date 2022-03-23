#include "TeddyBear.h"

#include "GraphicsObject_TextureLight.h"
#include "../Gemini Engine/ModelManager.h"
#include "../Gemini Engine/ShaderManager.h"
#include "../Gemini Engine/TextureManager.h"
#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/Scene.h"

#include "../Gemini Engine/Visualizer.h"
#include "../Gemini Engine/Colors.h"

#include "GameManager.h"

TeddyBear::TeddyBear(float angle, Vect pos)
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_Bear = new GraphicsObject_TextureLight(ModelManager::Get("TeddyBear"), ShaderManager::Get("TextureLight"), 
		TextureManager::Get("TeddyBearTex"), 
		LightColor, LightPos);

	SubmitDrawRegistration();
	
	float s = 40.0f;
	Scale = Matrix(SCALE, s, s, s);
	this->angle = angle;
	Matrix Rot = Matrix(ROT_X, -1.5708f) * Matrix(ROT_Y, angle);

	Pos = pos;
	RotTrans = Rot * Matrix(TRANS, Pos);

	Matrix world = Scale * RotTrans;
	pGObj_Bear->SetWorld(world);

	SetColliderModel(pGObj_Bear->getModel());
	UpdateCollisionData(world);
	SetCollidableGroup<TeddyBear>();
	SubmitCollisionRegistration();

	health = 1.0f;
}

TeddyBear::~TeddyBear()
{
	delete pGObj_Bear;
}

void TeddyBear::Draw()
{
	pGObj_Bear->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void TeddyBear::Collision(Bomb*)
{
	health -= 1.0f;

	if (health == 0.0f)
	{
		Matrix Rot = Matrix(ROT_Z, angle + 1.5708f);

		RotTrans = Rot * Matrix(TRANS, 0, 10, 0) * Matrix(TRANS, Pos);

		Matrix world = Scale * RotTrans;
		pGObj_Bear->SetWorld(world);

		GameManager::EnemyKilled();

		SubmitCollisionDeregistration();
	}
}