#include "../Gemini Engine/Gemini.h"

#include "../User Code/GameManager.h"

void Gemini::GameEnd()
{
	GameManager::Delete();
}