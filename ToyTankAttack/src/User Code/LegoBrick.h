#ifndef LegoBrick_
#define LegoBrick_

#include "Obstacle.h"
#include "Matrix.h"
#include "../Gemini Engine/Colors.h"

class GraphicsObject_TextureLight;
class Tank;

class LegoBrick : public Obstacle
{
public:
	// ---- BIG FOUR ---- //
	LegoBrick() = delete;
	LegoBrick(const LegoBrick&) = delete;
	LegoBrick& operator= (const LegoBrick&) = delete;
	~LegoBrick();
	
	LegoBrick(std::string color, Vect pos);


	// ---- GAME OBJECT METHODS ---- //
	virtual void Draw();

	// ---- COLLISION ---- //
	void Collision(Tank*) { };


private:
	GraphicsObject_TextureLight* pGObj_Lego;

};


#endif LegoBrick_
