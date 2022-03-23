#ifndef FloorPlane_
#define FloorPlane_

#include "../Gemini Engine/GameObject.h"


class GraphicsObject_TextureFlat;
class GraphicsObject_ColorNoTexture;

class FloorPlane : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	FloorPlane();
	FloorPlane(const FloorPlane&) = delete;
	FloorPlane& operator= (const FloorPlane&) = delete;
	~FloorPlane();

	virtual void Draw();

private:
	GraphicsObject_TextureFlat* pGObj_Floor;
	GraphicsObject_TextureFlat* pGObj_Wall_1;
	GraphicsObject_TextureFlat* pGObj_Wall_2;
	GraphicsObject_TextureFlat* pGObj_Wall_3;
	GraphicsObject_TextureFlat* pGObj_Wall_4;

};


#endif FloorPlane_
