#include "FloorPlane.h"

#include "GraphicsObject_TextureFlat.h"
#include "GraphicsObject_ColorNoTexture.h"
#include "../Gemini Engine/ModelManager.h"
#include "../Gemini Engine/ShaderManager.h"
#include "../Gemini Engine/TextureManager.h"

#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/Scene.h"


FloorPlane::FloorPlane()
{
	Model* plane = ModelManager::Get("FloorPlane");


	// graphics object
	pGObj_Floor = new GraphicsObject_TextureFlat(plane, ShaderManager::Get("TextureFlat"), TextureManager::Get("WoodFloorTex"));
	pGObj_Wall_1 = new GraphicsObject_TextureFlat(plane, ShaderManager::Get("TextureFlat"), TextureManager::Get("StarWallpaperTex"));
	pGObj_Wall_2 = new GraphicsObject_TextureFlat(plane, ShaderManager::Get("TextureFlat"), TextureManager::Get("StarWallpaperTex"));
	pGObj_Wall_3 = new GraphicsObject_TextureFlat(plane, ShaderManager::Get("TextureFlat"), TextureManager::Get("StarWallpaperTex"));
	pGObj_Wall_4 = new GraphicsObject_TextureFlat(plane, ShaderManager::Get("TextureFlat"), TextureManager::Get("StarWallpaperTex"));

	float scale = 1.0f;
	Matrix world = Matrix(SCALE, scale, scale, scale);
	pGObj_Floor->SetWorld(world);

	world = Matrix(ROT_Y, 3.14159f) * Matrix(ROT_X, 3.14159f * 0.5f) * Matrix(TRANS, 0.0f, 400.0f, -400.0f);
	pGObj_Wall_1->SetWorld(world);

	world = Matrix(ROT_X, 3.14159f * -0.5f) * Matrix(TRANS, 0.0f, 400.0f, 400.0f);
	pGObj_Wall_3->SetWorld(world);

	world = Matrix(ROT_Z, 3.14159f * 0.5f) * Matrix(ROT_X, 3.14159f * -0.5f) * Matrix(TRANS, 400.0f, 400.0f, 0.0f);
	pGObj_Wall_2->SetWorld(world);

	world = Matrix(ROT_Y, 3.14159f) * Matrix(ROT_Z, 3.14159f * -0.5f) * Matrix(ROT_X, 3.14159f * 0.5f) * Matrix(TRANS, -400.0f, 400.0f, 0.0f);
	pGObj_Wall_4->SetWorld(world);

	SubmitDrawRegistration();

	SubmitKeyRegistration(AZUL_KEY::KEY_C, EVENT_TYPE::KEY_PRESS);
}


void FloorPlane::Draw()
{
	pGObj_Floor->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	pGObj_Wall_1->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	pGObj_Wall_2->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	pGObj_Wall_3->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
	pGObj_Wall_4->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

FloorPlane::~FloorPlane()
{
	delete pGObj_Floor;
	delete pGObj_Wall_1;
	delete pGObj_Wall_2;
	delete pGObj_Wall_3;
	delete pGObj_Wall_4;
}