#include "CameraManager.h"

#include "Camera.h"
#include "Gemini.h"

//-----------------------------------------------------------------------------
// Constructor
//		Creating the DefaultCamera
//-----------------------------------------------------------------------------
CameraManager::CameraManager()
{
	// --- DEFAULT PERSPECTIVE (3D) CAMERA --- //
	DefaultCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	DefaultCamera->setViewport(0, 0, Gemini::GetWidth(), Gemini::GetHeight());
	DefaultCamera->setPerspective(35.0f, float(Gemini::GetWidth()) / float(Gemini::GetHeight()), 1.0f, 5000.0f);

	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	DefaultCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	DefaultCamera->updateCamera();  // Note: if the camera moves/changes, we need to call update again

	// Setting DefaultCamera as the currCamera
	camCurrent = DefaultCamera;


	// --- DEFAULT ORTHOGRAPPHIC CAMERA (2D) --- //
	Default2DCamera = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	Default2DCamera->setViewport(0, 0, Gemini::GetWidth(), Gemini::GetHeight());
	Default2DCamera->setOrthographic(-0.5f * Gemini::GetWidth(), 0.5f * Gemini::GetWidth(),
		-0.5f * Gemini::GetHeight(), 0.5f * Gemini::GetHeight(), 1.0f, 1000.0f);

	// Orient Camera
	Vect up2DCam = Vect(0.0f, 1.0f, 0.0f);
	Vect pos2DCam = Vect(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam = Vect(0.0f, 0.0f, -1.0f);
	Default2DCamera->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);

	Default2DCamera->updateCamera();
}

//-----------------------------------------------------------------------------
// CameraManager::GetCurrentCamera()
//		Returns a pointer to the current active camera
//-----------------------------------------------------------------------------
Camera* CameraManager::GetCurrentCamera()
{
	return camCurrent;
}

Camera* CameraManager::Get2DCamera()
{
	return Default2DCamera;
}

//-----------------------------------------------------------------------------
// CameraManager::SetCurrentCamera(Camera* newcam)
//		Sets the current active camera to the camera passed in as a parameter
//-----------------------------------------------------------------------------
void CameraManager::SetCurrentCamera(Camera* newcam)
{
	camCurrent = newcam;
}

CameraManager::~CameraManager()
{
	delete DefaultCamera;
	delete Default2DCamera;
}