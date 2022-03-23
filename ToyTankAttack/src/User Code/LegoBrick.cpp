#include "LegoBrick.h"

#include "GraphicsObject_TextureLight.h"
#include "../Gemini Engine/ModelManager.h"
#include "../Gemini Engine/ShaderManager.h"
#include "../Gemini Engine/TextureManager.h"
#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/Scene.h"
#include "../Gemini Engine/Visualizer.h"


LegoBrick::LegoBrick(std::string color, Vect pos)
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pGObj_Lego = new GraphicsObject_TextureLight(ModelManager::Get("LegoBrick"), ShaderManager::Get("TextureLight"),
		TextureManager::Get(color),
		LightColor, LightPos);

	SubmitDrawRegistration();

	float s = 1.0f;
	Matrix LegoScale = Matrix(SCALE, s, s, s);
	Matrix LegoRot = Matrix(ROT_Y, 0);
	Matrix LegoRotTrans = LegoRot * Matrix(TRANS, pos);

	Matrix world = LegoScale * LegoRotTrans;
	pGObj_Lego->SetWorld(world);

	SetColliderModel(pGObj_Lego->getModel());
	UpdateCollisionData(world);
	SetCollidableGroup<Obstacle>();
	SubmitCollisionRegistration();

}

LegoBrick::~LegoBrick()
{
	delete pGObj_Lego;
}

void LegoBrick::Draw()
{
	pGObj_Lego->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}