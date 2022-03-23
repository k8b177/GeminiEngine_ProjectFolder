#ifndef TeddyBear_
#define TeddyBear_

#include "../Gemini Engine/GameObject.h"
#include "Matrix.h"

class GraphicsObject_TextureLight;
class Tank;

class Bomb;

class TeddyBear : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	TeddyBear() = delete;
	TeddyBear(const TeddyBear&) = delete;
	TeddyBear& operator= (const TeddyBear&) = delete;
	~TeddyBear();

	TeddyBear(float angle, Vect pos);

	// ---- GAME OBJECT METHODS ---- //
	virtual void Draw();
	void Collision(Bomb*);


private:
	GraphicsObject_TextureLight* pGObj_Bear;

	Matrix Scale;
	float angle;
	Matrix RotTrans;
	Vect Pos;

	float health;

};


#endif TeddyBear_
