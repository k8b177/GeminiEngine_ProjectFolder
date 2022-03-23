#include "GodCam.h"

#include "Camera.h"
#include "../Gemini Engine/Gemini.h"
#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/Scene.h"

GodCam::GodCam()
{
	cam = new Camera(Camera::Type::PERSPECTIVE_3D);
	cam->setViewport(0, 0, Gemini::GetWidth(), Gemini::GetHeight());

	cam->setPerspective(35.0f, float(Gemini::GetWidth()) / float(Gemini::GetHeight()), 1.0f, 5000.0f);

	Vect initPos = Vect(50, 50, 100.0f);
	CamPos = initPos;
	CamRot = Matrix(IDENTITY);
	CamUp = Vect(0, 1, 0);
	CamDir = Vect(0, 0, 1);


	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	Vect Target(0, 0, 0);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);

	//		Second: we set the camera to its position and pointing toward the target
	cam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	cam->updateCamera();
}

GodCam::~GodCam()
{
	delete cam;
}

void GodCam::Update()
{
	// Camera translation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_F))
	{
		CamPos += Vect(0, 0, 1) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_V))
	{
		CamPos += Vect(0, 0, 1) * CamRot * -CamTranSpeed;
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_C))
	{
		CamPos += Vect(1, 0, 0) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_B))
	{
		CamPos += Vect(1, 0, 0) * CamRot * -CamTranSpeed;
	}

	// Camera Rotation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		CamRot *= Matrix(ROT_Y, CamRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		CamRot *= Matrix(ROT_Y, -CamRotSpeed);
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_UP))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, -CamRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, CamRotSpeed);
	}

	// Update the camera settings
	cam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	cam->updateCamera();
}

Camera* GodCam::GetCamera()
{
	return cam;
}