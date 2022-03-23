#ifndef GodCam_
#define GodCam_

#include "GameObject.h"
#include "Matrix.h"

class Camera;

class GodCam : public GameObject
{
public:
	// ---- BIG FOUR ---- //
	GodCam();
	GodCam(const GodCam&) = delete;
	GodCam& operator= (const GodCam&) = delete;
	~GodCam();

	virtual void Update();

	Camera* GetCamera();

private:
	Camera* cam;

	Vect CamPos;
	Matrix CamRot;
	Vect CamUp;
	Vect CamDir;
	float CamTranSpeed = 2;
	float CamRotSpeed = .02f;

};


#endif GodCam_
