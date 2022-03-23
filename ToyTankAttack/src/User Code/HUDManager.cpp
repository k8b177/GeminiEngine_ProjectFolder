#include "HUDManager.h"

#include "../Gemini Engine/GeminiSprite.h"

#include "../Gemini Engine/Gemini.h"

#include "../Gemini Engine/SpriteFontManager.h"
#include "../Gemini Engine/SpriteFont.h"
#include "../Gemini Engine/SpriteString.h"
#include "../Gemini Engine/ScreenLog.h"
#include "GameManager.h"


HUDManager::HUDManager(LevelEnum level)
{
	// sizing info for the health bar
	healthbarXAnchor = 10.0f;
	healthbarYAnchor = 10.0f;
	healthbarWidth = 300.0f;
	healthbarHeight = 30.0f;

	yellowRange = 0.6f;
	redRange = 0.3f;

	// create the sprites needed for the health bar
	pHealthBar = new GeminiSprite("HealthGreyImg");
	pHealthBar->SetScalePixel(healthbarWidth, healthbarHeight);
	pHealthBar->SetPosition(healthbarXAnchor, healthbarYAnchor);
	pHealthBar->SetCenter(-healthbarWidth * 0.5f, -healthbarHeight * 0.5f);
	
	pGreenFill = new GeminiSprite("HealthGreenImg");
	pGreenFill->SetScalePixel(healthbarWidth, healthbarHeight);
	pGreenFill->SetPosition(healthbarXAnchor, healthbarYAnchor);
	pGreenFill->SetCenter(-healthbarWidth * 0.5f, -healthbarHeight * 0.5f);

	pYellowFill = new GeminiSprite("HealthYellowImg");
	pYellowFill->SetScalePixel(healthbarWidth, healthbarHeight);
	pYellowFill->SetPosition(healthbarXAnchor, healthbarYAnchor);
	pYellowFill->SetCenter(-healthbarWidth * 0.5f, -healthbarHeight * 0.5f);

	pRedFill = new GeminiSprite("HealthRedImg");
	pRedFill->SetScalePixel(healthbarWidth, healthbarHeight);
	pRedFill->SetPosition(healthbarXAnchor, healthbarYAnchor);
	pRedFill->SetCenter(-healthbarWidth * 0.5f, -healthbarHeight * 0.5f);


	// set the first fill to Green
	pHealthBarFill = pGreenFill;


	currLevel = level;

	// creating sprite fonts
	armyFont = SpriteFontManager::Get("ArmyFont");
	agencyFont = SpriteFontManager::Get("AgencyFont");

	// creating display sprite string
	if (currLevel == LevelEnum::LEVEL1)
		displayString = new SpriteString(armyFont, "LEVEL 1: GROUND ATTACK!", Gemini::GetWidth() * 0.5f, Gemini::GetHeight() * 0.5f);
	else if (currLevel == LevelEnum::LEVEL2)
		displayString = new SpriteString(armyFont, "LEVEL 2: AIR ATTACK!", Gemini::GetWidth() * 0.5f, Gemini::GetHeight() * 0.5f);

	displayString->Set(displayString->GetPosX() - 0.5f * displayString->GetWidth(), displayString->GetPosY() + 0.5f * displayString->GetHeight());




	// submitting for Event Registrations
	SubmitDrawRegistration();
	SubmitUpdateRegistration();
	SubmitAlarmRegistration(3.0f, AlarmableManager::ALARM_ID::ALARM_0);
}

void HUDManager::Update()
{

}

void HUDManager::Draw2D()
{
	pHealthBar->Render();
	pHealthBarFill->Render();

	displayString->Render();

	DrawObjectives();
}

void HUDManager::DrawObjectives()
{
	ScreenLog::Add("Objectives: ");
	if (currLevel == LevelEnum::LEVEL1)
		ScreenLog::Add("\tDestroy %d Enemy Tanks (%d/%d)", GameManager::GetNumEnemiesToKill(), GameManager::GetNumEnemiesKilled(), GameManager::GetNumEnemiesToKill());
	else if (currLevel == LevelEnum::LEVEL2)
		ScreenLog::Add("\tBomb %d Teddy Bears (%d/%d)", GameManager::GetNumEnemiesToKill(), GameManager::GetNumEnemiesKilled(), GameManager::GetNumEnemiesToKill());
}

void HUDManager::KeyPressed(AZUL_KEY)
{

}

void HUDManager::Alarm0()
{
	displayString->SetString("");
}

void HUDManager::UpdateHealth(float health)
{
	if (health < redRange)
		pHealthBarFill = pRedFill;
	else if (health < yellowRange)
		pHealthBarFill = pYellowFill;


	float newWidth = health * healthbarWidth;

	pHealthBarFill->SetScalePixel(newWidth, healthbarHeight);
}

void HUDManager::GameOver()
{
	displayString->SetString("Defeat!");
	displayString->Set(Gemini::GetWidth() * 0.5f - 0.5f * displayString->GetWidth(), Gemini::GetHeight() * 0.5f + 0.5f * displayString->GetHeight());
	UpdateHealth(0);
}

void HUDManager::Victory()
{
	displayString->SetString("Victory!");
	displayString->Set(Gemini::GetWidth() * 0.5f - 0.5f * displayString->GetWidth(), Gemini::GetHeight() * 0.5f + 0.5f * displayString->GetHeight());
}

HUDManager::~HUDManager()
{
	delete pHealthBar;
	delete pGreenFill;
	delete pYellowFill;
	delete pRedFill;

	delete displayString;

}