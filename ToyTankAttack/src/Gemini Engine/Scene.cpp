#include "Scene.h"


void Scene::Register(Updatable* up)
{
	UpdateMgr.Register(up);
}

void Scene::Register(Drawable* dr)
{
	DrawMgr.Register(dr);
}

void Scene::Register(float t, AlarmableManager::ALARM_ID id, Alarmable* al)
{
	AlarmMgr.Register(t, id, al);
}

void Scene::Register(AZUL_KEY k, EVENT_TYPE e, Inputable* in)
{
	KBEventMgr.Register(in, k, e);
}

void Scene::Deregister(Updatable* up)
{
	UpdateMgr.Deregister(up);
}

void Scene::Deregister(Drawable* dr)
{
	DrawMgr.Deregister(dr);
}

void Scene::Deregister(AlarmableManager::ALARM_ID id, Alarmable* al)
{
	AlarmMgr.Deregister(id, al);
}

void Scene::Deregister(AZUL_KEY k, EVENT_TYPE e, Inputable* in)
{
	KBEventMgr.Deregister(in, k, e);
}

void Scene::SubmitCommand(CommandBase* cmd)
{
	RegistrationBrkr.addCommand(cmd);
}

void Scene::Update()
{
	// Process all registration/ deregistration before starting the new frame
	RegistrationBrkr.ExecuteCommands();

	// Check AlarmMgr to see if we need to trigger any alarms
	AlarmMgr.ProcessAlarms();

	// Checking KeyInputs for all objects that are watching keys
	KBEventMgr.ProcessKeyEvents();

	// Calling "Update" on all active Updatable objects in the scene
	UpdateMgr.ProcessElements();

	// Check if any collision pairs we are watching have a collision
	CollisionMgr.ProcessCollisions();
}

void Scene::Draw()
{
	DrawMgr.ProcessElements();
}

Camera* Scene::GetCurrentCamera()
{
	return CamMgr.GetCurrentCamera();
}

Camera* Scene::Get2DCamera()
{
	return CamMgr.Get2DCamera();
}

void Scene::SetCurrentCamera(Camera* cam)
{
	CamMgr.SetCurrentCamera(cam);
}