#ifndef CollisionDispatch_
#define CollisionDispatch_

#include "CollisionDispatchBase.h"

template <typename C1, typename C2>
class CollisionDispatch : public CollisionDispatchBase
{
private:

public:
	// ---- BIG FOUR ---- //
	CollisionDispatch() = default;
	CollisionDispatch(const CollisionDispatch&) = delete;
	CollisionDispatch& operator= (const CollisionDispatch&) = delete;
	virtual ~CollisionDispatch() = default;

	virtual void ProcessCallbacks(Collidable* c1, Collidable* c2) override
	{
		// safe to do the downcasting because this Dispatch *knows* the derived types from its creation
		C1* pDerCol1 = static_cast<C1*>(c1);
		C2* pDerCol2 = static_cast<C2*>(c2);

		pDerCol1->Collision(pDerCol2);
		pDerCol2->Collision(pDerCol1);
	}
};

#endif CollisionDispatch_