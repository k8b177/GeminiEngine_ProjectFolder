#ifndef CollisionTestSelfCommand_
#define CollisionTestSelfCommand_

#include "CollisionTestCommandBase.h"

class CollisionDispatchBase;
class CollidableGroup;

class CollisionTestSelfCommand : public CollisionTestCommandBase
{
private:
	CollisionDispatchBase* pDispatch;
	CollidableGroup* pG;


public:
	// ---- BIG FOUR ---- //
	CollisionTestSelfCommand() = default;
	CollisionTestSelfCommand(const CollisionTestSelfCommand&) = delete;
	CollisionTestSelfCommand& operator= (const CollisionTestSelfCommand&) = delete;
	~CollisionTestSelfCommand();

	CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* pd);

	virtual void Execute() override;
};

#endif CollisionTestSelfCommand_