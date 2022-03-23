#include "Bed.h"

#include "GraphicsObject_TextureLight.h"
#include "../Gemini Engine/ModelManager.h"
#include "../Gemini Engine/ShaderManager.h"
#include "../Gemini Engine/TextureManager.h"
#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/Scene.h"
#include "../Gemini Engine/Visualizer.h"
#include "../Gemini Engine/Colors.h"

Bed::Bed()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	Texture* tex = TextureManager::Get("BedTex");
	pGObj = new GraphicsObject_TextureLight(ModelManager::Get("Bed"), ShaderManager::Get("TextureLight"),
		tex, tex, tex, tex,
		LightColor, LightPos);

	SubmitDrawRegistration();

	float s = 200.0f;
	Matrix Scale = Matrix(SCALE, s, s, s);
	Matrix Rot = Matrix(ROT_Z, 3.14159f) * Matrix(ROT_X, -3.14159f * 0.5f);
	Matrix RotTrans = Rot * Matrix(TRANS, 275, -20.0f, 175);

	Matrix world = Scale * RotTrans;
	pGObj->SetWorld(world);

	SetColliderModel(pGObj->getModel());
	UpdateCollisionData(world);

	SetCollidableGroup<Bed>();
	SubmitCollisionRegistration();

}

Bed::~Bed()
{
	delete pGObj;
}

void Bed::Draw()
{
	pGObj->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}