#ifndef SceneAttorney_
#define SceneAttorney_

#include "Scene.h"
#include "SceneManager.h"

class CollisionManager;

class SceneAttorney
{
	// ---- BIG FOUR ---- //
	SceneAttorney() = default;
	SceneAttorney(const SceneAttorney&) = delete;
	SceneAttorney& operator= (const SceneAttorney&) = delete;
	~SceneAttorney() = default;

public:
	// methods in Scene only available to SceneManager
	class Manager
	{
	private:
		friend class SceneManager;
		static void Update(Scene* p) { p->Update(); };
		static void Draw(Scene* p) { p->Draw(); };
	};

public:
	// methods in Scene only available to <X>ables
	class XAblesAccess
	{
		friend class Updatable;
		friend class Drawable;
		friend class Alarmable;
		friend class Inputable;
		friend class Collidable;
		friend class GameObject;

	private:
		static void Register(Scene* s, Updatable* up) { s->Register(up); }
		static void Register(Scene* s, Drawable* dr) { s->Register(dr); }
		static void Register(Scene* s, float t, AlarmableManager::ALARM_ID id, Alarmable* al) { s->Register(t, id, al); }
		static void Register(Scene* s, AZUL_KEY k, EVENT_TYPE e, Inputable* in) { s->Register(k, e, in); }
		static void Deregister(Scene* s, Updatable* up) { s->Deregister(up); }
		static void Deregister(Scene* s, Drawable* dr) { s->Deregister(dr); }
		static void Deregister(Scene* s, AlarmableManager::ALARM_ID id, Alarmable* al) { s->Deregister(id, al); }
		static void Deregister(Scene* s, AZUL_KEY k, EVENT_TYPE e, Inputable* in) { s->Deregister(k, e, in); }
		static void SubmitCommand(Scene* s, CommandBase* cmd) { s->SubmitCommand(cmd); }

		static CollisionManager* GetCollisionMgr() { return &(SceneManager::GetCurrentScene()->CollisionMgr); }
		static AlarmableManager* GetAlarmableMgr() { return &(SceneManager::GetCurrentScene()->AlarmMgr); }
	};
};

#endif SceneAttorney_
