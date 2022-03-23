#ifndef CameraManager_
#define CameraManager_

class Camera;

class CameraManager
{
public:
	// ---- BIG FOUR ---- //
	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator= (const CameraManager&) = delete;
	~CameraManager();

	Camera* GetCurrentCamera();
	Camera* Get2DCamera();
	void SetCurrentCamera(Camera* newcam);

private:
	// ---- PRIVATE MEMBER VARS ---- //
	Camera* camCurrent;
	Camera* DefaultCamera;
	Camera* Default2DCamera;
	
};

#endif CameraManager_