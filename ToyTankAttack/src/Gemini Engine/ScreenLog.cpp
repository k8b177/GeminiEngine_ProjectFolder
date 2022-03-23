#include "ScreenLog.h"

#include "SpriteString.h"
#include "Gemini.h"
#include "SpriteFontManager.h"

#include "DebugOut.h"

ScreenLog* ScreenLog::ptrInstance = nullptr;

// initialize default character buffer
char ScreenLog::DebugBuff[256];

ScreenLog& ScreenLog::Instance()
{
	if (!ptrInstance)
		ptrInstance = new ScreenLog();
	return *ptrInstance;
}

ScreenLog::ScreenLog()
{
	anchorX = 0.0f;
	anchorY = (float)Gemini::GetHeight();

	SpriteFontManager::Load("DebugFont", "KristenITC25");

	font = SpriteFontManager::Get("DebugFont");
}

void ScreenLog::Add(char* A, ...)
{
	va_list args;

	va_start(args, A);
	vsprintf_s(DebugBuff, A, args);
	va_end(args);

	std::string s(DebugBuff);
	Instance().messages.push_back(s);
}

void ScreenLog::privRender()
{
	SpriteString* s;
	float xPos = anchorX;
	float yPos = anchorY;

	// loop through all of the strings added within the last frame, create spritestrings for them, and render them
	for (Message m : messages)
	{
		s = mySpriteStringPool.GetSpriteString();
		s->Set(font, m, xPos, yPos);
		s->Render();
		yPos -= s->GetHeight();

		mySpriteStringPool.ReturnSpriteString(s);
	}

	messages.clear();
	//DebugMsg::out("%d", messages.size());
}

void ScreenLog::Delete()
{
	delete ptrInstance;
}