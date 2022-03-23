#ifndef GeminiSprite_
#define GeminiSprite_

#include "Matrix.h"

class GraphicsObject_Sprite;
struct Rect;

class GeminiSprite
{
public:
	// ---- BIG FOUR ---- //
	GeminiSprite() = delete;
	GeminiSprite(const GeminiSprite&) = delete;
	GeminiSprite& operator= (const GeminiSprite&) = delete;
	~GeminiSprite();

	GeminiSprite(std::string imgKey);
	GeminiSprite(std::string imgKey, Rect* r);

	float GetAngle();
	void SetAngle(float a);
	void SetCenter(float xoffset, float yoffset);
	void SetPosition(float x, float y);
	void SetScaleFactor(float xscale, float yscale);
	void SetScalePixel(float width, float height);

	void Render();

	float GetOrigWidth();
	float GetOrigHeight();

private:
	float angle;
	float centerX; //relative to the sprite NOT absolute screen coordinates
	float centerY;
	Vect CenterVect;
	float scaleX;
	float scaleY;
	GraphicsObject_Sprite* pGOSprite;

	Matrix Scale;
	Matrix Rot;
	Matrix Trans;
	Matrix World;

	void UpdateWorldMatrix();
	void Initialize();
};

#endif GeminiSprite_
