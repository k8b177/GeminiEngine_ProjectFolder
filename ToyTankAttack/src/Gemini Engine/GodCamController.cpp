#include "GodCamController.h"

#include "GodCam.h"

#include "SceneManager.h"
#include "Scene.h"

GodCamController* GodCamController::ptrInstance = nullptr;

GodCamController& GodCamController::Instance()
{
	if (!ptrInstance)
		ptrInstance = new GodCamController();
	return *ptrInstance;
}

GodCamController::GodCamController()
	:pLastUserCam(nullptr)
{
	pGodCam = new GodCam();
}

void GodCamController::Delete()
{
	delete Instance().pGodCam;

	delete ptrInstance;
}

void GodCamController::privSwitchToGodCam()
{
	// save the user's curr camera
	pLastUserCam = SceneManager::GetCurrentScene()->GetCurrentCamera();

	// set the current camera to the god camera
	SceneManager::GetCurrentScene()->SetCurrentCamera(pGodCam->GetCamera());

	// "Activate" the god cam
	pGodCam->SubmitUpdateRegistration();
}

void GodCamController::privSwitchToLastUserCam()
{
	// set the current camera to the user's last camera
	SceneManager::GetCurrentScene()->SetCurrentCamera(pLastUserCam);

	// "De-activate" the god cam
	pGodCam->SubmitUpdateDeregistration();
}
