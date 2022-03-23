#ifndef CollisionDispatchBase_
#define CollisionDispatchBase_

class Collidable;

class CollisionDispatchBase
{
private:

public:
	// ---- BIG FOUR ---- //
	CollisionDispatchBase() = default;
	CollisionDispatchBase(const CollisionDispatchBase&) = delete;
	CollisionDispatchBase& operator= (const CollisionDispatchBase&) = delete;
	virtual ~CollisionDispatchBase() = default;


	virtual void ProcessCallbacks(Collidable* c1, Collidable* c2) = 0;
};

#endif CollisionDispatchBase_