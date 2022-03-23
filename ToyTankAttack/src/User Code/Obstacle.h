#ifndef Obstacle_
#define Obstacle_

#include "../Gemini Engine/GameObject.h"

class Tank;
class Enemy;
class Bullet;
class EnemyBullet;
class ToyPlane;

class Obstacle : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	Obstacle() = default;
	Obstacle(const Obstacle&) = delete;
	Obstacle& operator= (const Obstacle&) = delete;
	virtual ~Obstacle() = default;

	// ---- COLLISION ---- //
	void Collision(Tank*) {};
	void Collision(Enemy*) {};

	void Collision(Bullet*) {};
	void Collision(EnemyBullet*) {};

	void Collision(ToyPlane*) {};

};


#endif Obstacle_
