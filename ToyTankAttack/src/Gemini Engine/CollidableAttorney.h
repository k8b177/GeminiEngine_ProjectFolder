#ifndef CollidableAttorney_
#define CollidableAttorney_

#include "Collidable.h"

class CollidableAttorney
{
	// ---- BIG FOUR ---- //
	CollidableAttorney() = default;
	CollidableAttorney(const CollidableAttorney&) = delete;
	CollidableAttorney& operator= (const CollidableAttorney&) = delete;
	~CollidableAttorney() = default;

/*
public:
	// methods in Updatable only available to UpdatableManager
	class Manager
	{
	private:
		friend class UpdatableManager;
		static void Update(Updatable* p) { p->Update(); };
		static void SetDeleteRef(Updatable* p, UpdatableManager::StorageListRef ref) { p->SetDeleteRef(ref); }
		static UpdatableManager::StorageListRef GetDeleteRef(Updatable* p) { return p->GetDeleteRef(); }
	};
*/

public:
	// methods in Collidable only available to CollisionRegistrationCommand and CollisionDeregistrationCommand
	class Registration
	{
		friend class CollisionRegistrationCommand;
		friend class CollisionDeregistrationCommand;
	private:
		static void SceneRegistration(Collidable* p) { p->SceneRegistration(); }
		static void SceneDeregistration(Collidable* p) { p->SceneDeregistration(); }
	};
};

#endif CollidableAttorney_
