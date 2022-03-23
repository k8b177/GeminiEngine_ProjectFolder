#ifndef CameraController_
#define CameraController_

#include "Vect.h"
#include "Matrix.h"
#include "../Gemini Engine/GameObject.h"

class Camera;
class Player;
class ToyPlane;

class CameraController : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	CameraController() = delete;
	CameraController(const CameraController&) = delete;
	CameraController& operator= (const CameraController&) = delete;
	~CameraController();

	CameraController(Player* p, Vect initPos);

	virtual void Update();
	virtual void KeyPressed(AZUL_KEY k);

	void SetCamera(Camera* c);
	void SetCamOffset(Matrix m);

private:
	// Camera vars
	Vect CamPosVect;
	Matrix CamPos;
	Matrix CamRot;
	Vect CamUp;	
	Vect CamDir;
	float CamTranSpeed = 2;
	float CamRotSpeed = .02f;

	Camera* mainCam;
	Player* pPlayer;

	Matrix CamOffset;

};


#endif CameraController_
