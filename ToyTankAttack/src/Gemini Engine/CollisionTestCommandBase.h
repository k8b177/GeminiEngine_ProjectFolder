#ifndef CollisionTestCommandBase_
#define CollisionTestCommandBase_

class CollisionTestCommandBase
{
private:

public:
	// ---- BIG FOUR ---- //
	CollisionTestCommandBase() = default;
	CollisionTestCommandBase(const CollisionTestCommandBase&) = delete;
	CollisionTestCommandBase& operator= (const CollisionTestCommandBase&) = delete;
	virtual ~CollisionTestCommandBase() = default;


	virtual void Execute() = 0;
};

#endif CollisionTestCommandBase_