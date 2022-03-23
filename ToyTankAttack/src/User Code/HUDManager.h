#ifndef HUDManager_
#define HUDManager_

#include "../Gemini Engine/GameObject.h"
#include "Matrix.h"
#include "LevelEnum.h"

class GeminiSprite;
class SpriteFont;
class SpriteString;

class HUDManager : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	HUDManager() = delete;
	HUDManager(const HUDManager&) = delete;
	HUDManager& operator= (const HUDManager&) = delete;
	~HUDManager();

	HUDManager(LevelEnum level);

	virtual void Update();
	virtual void Draw2D();
	virtual void KeyPressed(AZUL_KEY k);
	virtual void Alarm0();

	void UpdateHealth(float health);
	void GameOver();
	void Victory();
	void DrawObjectives();

private:
	LevelEnum currLevel;

	GeminiSprite* pHealthBar;
	GeminiSprite* pHealthBarFill;

	GeminiSprite* pGreenFill;
	GeminiSprite* pYellowFill;
	GeminiSprite* pRedFill;

	float yellowRange;
	float redRange;

	SpriteFont* armyFont;
	SpriteFont* agencyFont;
	SpriteString* displayString;


	float healthbarXAnchor;
	float healthbarYAnchor;
	float healthbarHeight;
	float healthbarWidth;

	bool gameOverDisplayed = false;



};


#endif HUDManager_
