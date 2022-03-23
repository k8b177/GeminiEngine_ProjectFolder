#ifndef InputableAttorney_
#define InputableAttorney_

#include "Inputable.h"
#include "SingleKeyEventManager.h"

class InputableAttorney
{
	// ---- BIG FOUR ---- //
	InputableAttorney() = default;
	InputableAttorney(const InputableAttorney&) = delete;
	InputableAttorney& operator= (const InputableAttorney&) = delete;
	~InputableAttorney() = default;

public:
	// methods in Inputable only available to InputableManager
	class Manager
	{
	private:
		friend class SingleKeyEventManager;
		static void KeyPressed(Inputable* p, AZUL_KEY k) { p->KeyPressed(k); };
		static void KeyReleased(Inputable* p, AZUL_KEY k) { p->KeyReleased(k); }
		static void SetDeleteRef(Inputable* p, AZUL_KEY k, EVENT_TYPE e, SingleKeyEventManager::InputableCollectionRef sk_ref) { p->SetDeleteRef(k, e, sk_ref); }
		static SingleKeyEventManager::InputableCollectionRef GetDeleteRef(AZUL_KEY k, EVENT_TYPE e, Inputable* p) { return p->GetDeleteRef(k, e); }
	};

public:
	// methods in Inputable only available to KeyRegistrationCommand and KeyDeregistrationCommand
	class Registration
	{
		friend class KeyRegistrationCommand;
		friend class KeyDeregistrationCommand;
	private:
		static void KeyRegistration(Inputable* p, Inputable::DataMapEntryRef in_ref, AZUL_KEY k, EVENT_TYPE e) { p->SceneRegistration(in_ref, k, e); }
		static void KeyDeregistration(Inputable* p, Inputable::DataMapEntryRef in_ref, AZUL_KEY k, EVENT_TYPE e) { p->SceneDeregistration(in_ref, k, e); }
	};
};

#endif InputableAttorney_
