#ifndef UpdatableAttorney_
#define UpdatableAttorney_

#include "Updatable.h"

class UpdatableAttorney
{
	// ---- BIG FOUR ---- //
	UpdatableAttorney() = default;
	UpdatableAttorney(const UpdatableAttorney&) = delete;
	UpdatableAttorney& operator= (const UpdatableAttorney&) = delete;
	~UpdatableAttorney() = default;

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

public:
	// methods in Updatable only available to UpdateRegistrationCommand and UpdateDeregistrationCommand
	class Registration
	{
		friend class UpdateRegistrationCommand;
		friend class UpdateDeregistrationCommand;
	private:
		static void SceneRegistration(Updatable* p) { p->SceneRegistration(); }
		static void SceneDeregistration(Updatable* p) { p->SceneDeregistration(); }
	};
};

#endif UpdatableAttorney_
