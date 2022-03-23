#include "Cottage.h"

#include "Vect.h"
#include "GraphicsObject_TextureLight.h"
#include "DebugOut.h"
#include "../Gemini Engine/ModelManager.h"
#include "../Gemini Engine/ShaderManager.h"
#include "../Gemini Engine/TextureManager.h"

#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/Scene.h"
#include "../Gemini Engine/Visualizer.h"
#include "../Gemini Engine/Colors.h"



Cottage::Cottage()
{
	// Creating Graphics Object for Cottage
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObjLT = new GraphicsObject_TextureLight(ModelManager::Get("Cottage"), 
												ShaderManager::Get("TextureLight"), 
												TextureManager::Get("CottageBrickTex"),
												TextureManager::Get("CottageRoofTex"),
												TextureManager::Get("CottageDoorTex"), 
												TextureManager::Get("CottageChimneyTex"), LightColor, LightPos);


	// Setting Up Cottage
	Scale.set(SCALE, 2, 2, 2); // scale matrix
	RotTrans = Matrix(ROT_Y, 0) * Matrix(TRANS, 10, 0, 10); // translation matrix
	Matrix world = Scale * RotTrans;
	pGObjLT->SetWorld(world); // placing ship in the world

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	SubmitKeyRegistration(AZUL_KEY::KEY_T, EVENT_TYPE::KEY_PRESS);

	SetCollidableGroup<Cottage>();
	SubmitCollisionRegistration();

	SetColliderModel(pGObjLT->getModel()); // giving BoundingSphere a pointer to the Frigate Model
	UpdateCollisionData(pGObjLT->getWorld());
}

void Cottage::Update()
{

}

void Cottage::Draw()
{
	pGObjLT->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Cottage::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_T)
	{
		SubmitCollisionDeregistration();
	}
}

void Cottage::Collision(Frigate*)
{
	DebugMsg::out("Collision Cottage with Frigate\n");
}


Cottage::~Cottage()
{
	delete pGObjLT;
}