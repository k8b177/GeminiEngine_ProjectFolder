#include "../Gemini Engine/Gemini.h"

#include "../Gemini Engine/ModelManager.h"
#include "../Gemini Engine/TextureManager.h"
#include "../Gemini Engine/ShaderManager.h"
#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/ImageManager.h"
#include "../Gemini Engine/SpriteFontManager.h"


// Demo Game
#include "../User Code/MainScene.h"

void Gemini::LoadResources()
{
	
	ShaderManager::Load("ColorConstant", "colorConstantRender");
	ShaderManager::Load("TextureFlat", "textureFlatRender");
	ShaderManager::Load("TextureLight", "textureLightRender");
	ShaderManager::Load("ColorNoTexture", "colorNoTextureRender");


	ModelManager::Load("TankBody", "t99body.azul");
	ModelManager::Load("TankTurret", "t99turret.azul");
	ModelManager::Load("Bullet", "bullet_case.azul");
	ModelManager::Load("Bomb", Model::PreMadeModels::UnitSphere);
	ModelManager::Load("TeddyBear", "Bear.azul");
	ModelManager::Load("LegoBrick", "lego.azul");
	ModelManager::Load("ToyPlane", "toyPlane.azul");
	ModelManager::Load("Bed", "Bed.azul");
	ModelManager::Load("FloorPlane", 800, 8, 8);
	ModelManager::Load("Sphere", Model::PreMadeModels::UnitSphere);

	TextureManager::Load("Grey", 96, 96, 96);
	TextureManager::Load("Orange", 255, 165, 0);
	TextureManager::Load("ArmyGreen", 0, 102, 0);
	TextureManager::Load("Blue", 23, 81, 146);
	TextureManager::Load("Red", 255, 0, 0);
	TextureManager::Load("Yellow", 255, 255, 0);
	TextureManager::Load("HealthGrey", 211, 211, 211);
	TextureManager::Load("HealthGreen", 0, 255, 0);
	TextureManager::Load("HealthYellow", 255, 255, 0);
	TextureManager::Load("HealthRed", 255, 0, 0);
	TextureManager::Load("TeddyBearTex", "texbear2.tga");
	TextureManager::Load("MetalTex", "metal_rust.tga");
	TextureManager::Load("BodyTex", "body.tga");
	TextureManager::Load("TrackTex", "track.tga");
	TextureManager::Load("BulletTex", "bullet_tex.tga");
	TextureManager::Load("GroundTex", "seamless.tga");
	TextureManager::Load("ToyPlaneTex", "toyPlaneTex.tga");
	TextureManager::Load("BedTex", "BedTex2.tga");
	TextureManager::Load("StarWallpaperTex", "starWallpaper.tga");

	TextureManager::Load("WoodFloorTex", "woodFloor.tga");
	// Turning on anisotropic filtering for floor
	// Shoutout to Klaudius for the help
	{
		glBindTexture(GL_TEXTURE_2D, TextureManager::Get("WoodFloorTex")->getTextureID());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}


	ImageManager::Load("HealthGreyImg", TextureManager::Get("HealthGrey"));
	ImageManager::Load("HealthGreenImg", TextureManager::Get("HealthGreen"));
	ImageManager::Load("HealthYellowImg", TextureManager::Get("HealthYellow"));
	ImageManager::Load("HealthRedImg", TextureManager::Get("HealthRed"));


	SpriteFontManager::Load("ArmyFont", "Stencil60");
	SpriteFontManager::Load("AgencyFont", "AgencyFB");


	SceneManager::SetNextScene(new MainScene());
}