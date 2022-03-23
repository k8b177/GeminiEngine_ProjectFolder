#include "GeminiSprite.h"

#include "GraphicsObject_Sprite.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Gemini.h"
#include "Image.h"

GeminiSprite::GeminiSprite(std::string imgKey)
	:angle(0.0f), scaleX(1.0f), scaleY(1.0f)
{
	// Get the image for this imgKey
	Image* img = ImageManager::Get(imgKey);

	// Create the rect for the starting position and size of the sprite
	Rect* r = new Rect(0.0f, 0.0f, (float)img->pImageRect->width, (float)img->pImageRect->height);
	
	// Create the GraphicsObject_Sprite
	pGOSprite = new GraphicsObject_Sprite(ModelManager::Get("UnitSquareXY"),
			ShaderManager::Get("SpriteRender"), img, r);

	// cleanup r
	delete r;

	Initialize();
}

GeminiSprite::GeminiSprite(std::string imgKey, Rect* r)
	:angle(0.0f), scaleX(1.0f), scaleY(1.0f)
{
	// Create the GraphicsObject_Sprite
	pGOSprite = new GraphicsObject_Sprite(ModelManager::Get("UnitSquareXY"),
		ShaderManager::Get("SpriteRender"), ImageManager::Get(imgKey), r);

	Initialize();
}

void GeminiSprite::Initialize()
{
	// Start centerX and centerY at (0,0)
	// This is the middle of the sprite
	this->centerX = 0.0f;
	this->centerY = 0.0f;
	CenterVect = Vect(0.0f, 0.0f, 0.0f);

	// Default scale and rot
	Scale.set(SCALE, 1.0f, 1.0f, 1.0f);
	Rot.set(ROT_Z, 0.0f);
	// Trans starts in the middle of the sprite
	Trans.set(TRANS, pGOSprite->origPosX + 0.5f * pGOSprite->origWidth,	pGOSprite->origPosY - 0.5f*pGOSprite->origHeight, 0.0f);

	UpdateWorldMatrix();
}

GeminiSprite::~GeminiSprite()
{
	delete pGOSprite;
}

void GeminiSprite::Render()
{
	pGOSprite->Render(SceneManager::GetCurrentScene()->Get2DCamera());
}

float GeminiSprite::GetAngle()
{
	return angle;
}

void GeminiSprite::SetScaleFactor(float xscale, float yscale)
{
	this->scaleX = xscale;
	this->scaleY = yscale;
	Scale.set(SCALE, xscale, yscale, 1.0f);
	UpdateWorldMatrix();
}

void GeminiSprite::SetAngle(float a)
{
	// Set the new angle
	this->angle = a;

	// Create the Rotation matrix about the z axis for this angle
	Rot = Matrix(ROT_Z, angle);

	// Undo Center Offset (move the center of the sprite to where Trans is)
	Trans = Matrix(TRANS, CenterVect) * Trans;

	// Rotate the center offset to the new rotation
	CenterVect = Vect(centerX, centerY, 0.0f) * Rot;

	// Move the Trans matrix to the offset position
	Trans = Matrix(TRANS, -CenterVect) * Trans;

	UpdateWorldMatrix();
}

void GeminiSprite::SetPosition(float x, float y)
{
	// Using just the (TRANS, x, y) matrix would place the sprite's center at x, y
	// Need to multiply by the inverse of the CenterVect to offset the sprite correctly
	Trans = Matrix(TRANS, -CenterVect) * Matrix(TRANS, x, y, 0.0f);

	UpdateWorldMatrix();
}

void GeminiSprite::SetScalePixel(float width, float height)
{
	// x and y scale factors will be a ratio of the new width/height to the original sprite width/height
	float x = width / pGOSprite->origWidth;
	float y = height / pGOSprite->origHeight;

	SetScaleFactor(x, y);
}

void GeminiSprite::SetCenter(float xoffset, float yoffset)
{
	// Undo Center Offset
	Trans = Matrix(TRANS, CenterVect) * Trans;

	// Set new offset
	centerX = xoffset;
	centerY = yoffset;

	// Create new CenterVect with right rotation
	CenterVect = Vect(xoffset, yoffset, 0.0f) * Rot;

	// Move the Trans matrix to the offset position
	Trans = Matrix(TRANS, -CenterVect) * Trans;

	UpdateWorldMatrix();
}

void GeminiSprite::UpdateWorldMatrix()
{
	World = Scale * Rot * Trans;
	pGOSprite->SetWorld(this->World);
}


float GeminiSprite::GetOrigWidth()
{
	return pGOSprite->origWidth;
}

float GeminiSprite::GetOrigHeight()
{
	return pGOSprite->origHeight;
}