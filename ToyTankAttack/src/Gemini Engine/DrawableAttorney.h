#ifndef DrawableAttorney_
#define DrawableAttorney_

#include "Drawable.h"

class DrawableAttorney
{
	// ---- BIG FOUR ---- //
	DrawableAttorney() = default;
	DrawableAttorney(const DrawableAttorney&) = delete;
	DrawableAttorney& operator= (const DrawableAttorney&) = delete;
	~DrawableAttorney() = default;

public:
	// methods in Drawable only available to DrawableManager
	class Manager
	{
	private:
		friend class DrawableManager;
		static void Draw(Drawable* p) { p->Draw(); };
		static void Draw2D(Drawable* p) { p->Draw2D(); };
		static void SetDeleteRef(Drawable* p, DrawableManager::StorageListRef ref) { p->SetDeleteRef(ref); }
		static DrawableManager::StorageListRef GetDeleteRef(Drawable* p) { return p->GetDeleteRef(); }
	};

public:
	// methods in Drawable only available to DrawRegistrationCommand and DrawDeregistrationCommand
	class Registration
	{
		friend class DrawRegistrationCommand;
		friend class DrawDeregistrationCommand;
	private:
		static void SceneRegistration(Drawable* p) { p->SceneRegistration(); }
		static void SceneDeregistration(Drawable* p) { p->SceneDeregistration(); }
	};
};

#endif DrawableAttorney_
