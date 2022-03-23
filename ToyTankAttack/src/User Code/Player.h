#ifndef Player_
#define Player_

#include "../Gemini Engine/GameObject.h"

class Matrix;

class Player : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	Player() = default;
	Player(const Player&) = delete;
	Player& operator= (const Player&) = delete;
	virtual ~Player() = default;

	virtual Matrix& GetPlayerRotTrans() = 0;

};


#endif Player_
