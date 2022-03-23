#ifndef CollisionRegistrationCommand_
#define CollisionRegistrationCommand_

#include "CommandBase.h"

class Collidable;

class CollisionRegistrationCommand : public CommandBase
{
private:
	Collidable* ptrCol;

public:
	// ---- BIG FOUR ---- //
	CollisionRegistrationCommand() = delete;
	CollisionRegistrationCommand(const CollisionRegistrationCommand&) = delete;
	CollisionRegistrationCommand& operator= (const CollisionRegistrationCommand&) = delete;
	~CollisionRegistrationCommand() = default;

	CollisionRegistrationCommand(Collidable* col);


	virtual void Execute() override;
};

#endif CollisionRegistrationCommand_