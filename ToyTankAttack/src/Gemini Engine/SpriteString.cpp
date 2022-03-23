#include "SpriteString.h"

#include "SpriteFont.h"


SpriteString::SpriteString(SpriteFont* sf, std::string s, float x, float y)
{
	Set(sf, s, x, y);
}

float SpriteString::GetWidth()
{
	return width;
}

float SpriteString::GetHeight()
{
	return height;
}

float SpriteString::GetPosX()
{
	return posx;
}

float SpriteString::GetPosY()
{
	return posy;
}


void SpriteString::Set(float x, float y)
{
	posx = x;
	posy = y;
}


void SpriteString::Set(SpriteFont* sf, std::string s, float x, float y)
{
	// Set the sfont pointer
	sfont = sf;

	// Sets posx and posy
	Set(x, y);

	// Set string (glyph list)
	SetString(s);
}

void SpriteString::SetString(std::string s)
{
	// clear the glyph list
	glyphs.clear();

	// Get length
	int len = s.length();

	// Start width and height at 0
	width = 0;
	height = 0;

	Glyph* g;
	// Loop through the string, getting glyphs for each char and adding the glyph to the glyph list
	for (int i = 0; i < len; i++)
	{
		// get glyph for char at i
		g = sfont->GetGlyph(s.at(i));
		// add glyph to the glyph list
		glyphs.push_back(g);
		// add glyph's width to the overall width
		width += g->GetOrigWidth();

		// height should equal the height of the tallest glyph - if this glyph's height is taller than make its height the new height
		if (g->GetOrigHeight() > height)
			height = g->GetOrigHeight();
	}
}

void SpriteString::Render()
{
	float gPos = posx;
	for (Glyph* g : glyphs)
	{
		g->SetPosition(gPos, posy);
		g->Render();
		
		gPos += g->GetOrigWidth();
	}
}
