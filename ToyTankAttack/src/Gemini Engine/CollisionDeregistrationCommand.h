#ifndef CollisionDeregistrationCommand_
#define CollisionDeregistrationCommand_

#include "CommandBase.h"

class Collidable;

class CollisionDeregistrationCommand : public CommandBase
{
private:
	Collidable* ptrCol;

public:
	// ---- BIG FOUR ---- //
	CollisionDeregistrationCommand() = delete;
	CollisionDeregistrationCommand(const CollisionDeregistrationCommand&) = delete;
	CollisionDeregistrationCommand& operator= (const CollisionDeregistrationCommand&) = delete;
	~CollisionDeregistrationCommand() = default;

	CollisionDeregistrationCommand(Collidable* ptrUp);

	virtual void Execute() override;
};

#endif CollisionDeregistrationCommand_