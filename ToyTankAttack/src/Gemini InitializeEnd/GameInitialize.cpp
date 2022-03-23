#include "../Gemini Engine/Gemini.h"

void Gemini::GameInitialize()
{
	// Game Window Device setup
	Gemini::SetWindowName("Gemini Engine");
	Gemini::SetWidthHeight(800, 600);
	Gemini::SetClear(0.4f, 0.4f, 0.8f, 1.0f);

}