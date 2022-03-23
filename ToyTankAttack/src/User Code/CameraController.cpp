#include "CameraController.h"

#include "Camera.h"
#include "../Gemini Engine/Gemini.h"
#include "../Gemini Engine/SceneManager.h"
#include "../Gemini Engine/Scene.h"
#include "../Gemini Engine/GodCamController.h"

#include "Tank.h"
#include "Player.h"

CameraController::CameraController(Player* p, Vect initPos)
	:pPlayer(p)
{
	mainCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	mainCam->setViewport(0, 0, Gemini::GetWidth(), Gemini::GetHeight());

	mainCam->setPerspective(35.0f, float(Gemini::GetWidth()) / float(Gemini::GetHeight()), 1.0f, 5000.0f);

	CamPosVect = initPos;
	CamRot = Matrix(IDENTITY);
	CamUp = Vect(0, 1, 0);
	CamDir = Vect(0, 0, 1);


	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	// Vect Target(0, 0, 0);
	//Vect Target(0, 20, 20);
	Vect Target = pPlayer->GetPlayerRotTrans().get(MatrixRowType::ROW_3);
	CamRot.set(ROT_ORIENT, Target - CamPosVect, CamUp);

	//		Second: we set the camera to its position and pointing toward the target
	mainCam->setOrientAndPosition(CamUp * CamRot, CamPosVect + CamDir * CamRot, CamPosVect);
	mainCam->updateCamera();

	CamOffset = Matrix(TRANS, initPos);
	
	SubmitUpdateRegistration();
	SubmitKeyRegistration(AZUL_KEY::KEY_1, EVENT_TYPE::KEY_PRESS);
	SubmitKeyRegistration(AZUL_KEY::KEY_2, EVENT_TYPE::KEY_PRESS);

	SetCamera(mainCam);
}


void CameraController::SetCamera(Camera* c)
{
	SceneManager::GetCurrentScene()->SetCurrentCamera(c);
}

void CameraController::SetCamOffset(Matrix m)
{
	CamOffset = m;
}

void CameraController::Update()
{
	/*
	// Camera translation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		CamPos += Vect(0, 0, 1) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		CamPos += Vect(0, 0, 1) * CamRot * -CamTranSpeed;
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		CamPos += Vect(1, 0, 0) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		CamPos += Vect(1, 0, 0) * CamRot * -CamTranSpeed;
	}
	*/

	/*
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
	*/
	



	// Update the camera settings
	//mainCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	//mainCam->updateCamera();


	Matrix PlayerRotTrans = pPlayer->GetPlayerRotTrans();
	
	// Get the Turret's Translation and Rotation Matrices, separated
	Matrix PlayerTransTemp = Matrix(TRANS, PlayerRotTrans.get(MatrixRowType::ROW_3));
	Matrix PlayerRotTemp = Matrix(PlayerRotTrans.get(MatrixRowType::ROW_0),
		PlayerRotTrans.get(MatrixRowType::ROW_1), PlayerRotTrans.get(MatrixRowType::ROW_2),
		Vect(0, 0, 0, 1));

	// Position the Camera
	CamPos = CamOffset * PlayerRotTemp;
	CamPos = CamPos * PlayerTransTemp;

	CamPosVect = CamPos.get(ROW_3);

	Vect Target = pPlayer->GetPlayerRotTrans().get(MatrixRowType::ROW_3);
	CamRot.set(ROT_ORIENT, Target - CamPosVect, CamUp);

	//		Second: we set the camera to its position and pointing toward the target
	mainCam->setOrientAndPosition(CamUp * CamRot, CamPosVect + CamDir * CamRot, CamPosVect);
	mainCam->updateCamera();
}

void CameraController::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_1:
		GodCamController::SwitchToGodCam();
		break;
	case AZUL_KEY::KEY_2:
		GodCamController::SwitchToLastUserCam();
	}
}

CameraController::~CameraController()
{
	delete mainCam;
}

