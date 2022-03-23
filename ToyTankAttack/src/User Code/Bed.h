#ifndef Bed_
#define Bed_

#include "Obstacle.h"
#include "Matrix.h"

class GraphicsObject_TextureLight;
class Tank;

class Bed : public Obstacle
{
public:
	// ---- BIG FOUR ---- //
	Bed();
	Bed(const Bed&) = delete;
	Bed& operator= (const Bed&) = delete;
	~Bed();

	// ---- GAME OBJECT METHODS ---- //
	virtual void Draw();

	// ---- COLLISION ---- //
	void Collision(Tank*) { };


private:
	GraphicsObject_TextureLight* pGObj;

};


#endif Bed_
