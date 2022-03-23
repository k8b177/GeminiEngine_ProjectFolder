#ifndef CollisionTestPairCommand_
#define CollisionTestPairCommand_

#include "CollisionTestCommandBase.h"

class CollisionDispatchBase;
class CollidableGroup;

class CollisionTestPairCommand : public CollisionTestCommandBase
{
private:
	CollisionDispatchBase* pDispatch;
	CollidableGroup* pG1;
	CollidableGroup* pG2;


public:
	// ---- BIG FOUR ---- //
	CollisionTestPairCommand() = delete;
	CollisionTestPairCommand(const CollisionTestPairCommand&) = delete;
	CollisionTestPairCommand& operator= (const CollisionTestPairCommand&) = delete;
	~CollisionTestPairCommand();

	CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd);

	virtual void Execute() override;
};

#endif CollisionTestPairCommand_