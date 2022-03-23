#ifndef Cottage_
#define Cottage_

#include "../Gemini Engine/GameObject.h"
#include "Matrix.h"

class GraphicsObject_TextureLight;
class Frigate;

class Cottage : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	Cottage();
	Cottage(const Cottage&) = delete;
	Cottage& operator= (const Cottage&) = delete;
	~Cottage();

	virtual void Update();
	virtual void Draw();
	virtual void KeyPressed(AZUL_KEY k);

	void Collision(Frigate*);

private:
	GraphicsObject_TextureLight* pGObjLT;

	Matrix Scale;
	Matrix RotTrans;
};


#endif Cottage_
