
#ifndef GodCamController_
#define GodCamController_

class GodCam;
class Camera;

class GodCamController
{
	/// \cond
	friend class GodCamControllerAttorney;
private:
	static GodCamController* ptrInstance;

	static GodCamController& Instance();
	static void Delete();

	GodCam* pGodCam;
	Camera* pLastUserCam;

	void privSwitchToGodCam();
	void privSwitchToLastUserCam();
	
	// ---- BIG FOUR ---- //
	GodCamController();
	GodCamController(const GodCamController&) = delete;
	GodCamController& operator= (const GodCamController&) = delete;
	~GodCamController() = default;

	/// \endcond

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void GodCamController::SwitchToGodCam()
	///
	/// \brief	Switches to the God Camera
	/// 		
	/// Calling \b SwitchToGodCam() will change the scenes current camera to the God Cam and save your last scene camera internally.
	///
	/// When using the GodCam use the following keyboard controls to navigate:
	/// - \b Forward = \b F Key
	/// - \b Backward = \b V Key  
	/// - \b Right = \b B Key  
	/// - \b Left = \b C Key    
	/// 
	/// - \b RotateUp = \b UpArrow Key  
	/// - \b RotateDown = \b DownArrow Key
	/// - \b RotateRight = \b RightArrow Key  
	/// - \b RotateLeft = \b LeftArrowKey
	///
	///	\par Example
	///		In the following example, the user has created a CameraController Game Object to manager their camera.
	///		They have set up key events to switch between the GodCam and their scene camera.
	///
	///	\code
	///	void CameraController::KeyPressed(AZUL_KEY k)
	/// {
	///		switch (k)
	///		{
	///		// if "1" key pressed, switch to GodCam
	///		case AZUL_KEY::KEY_1:
	///			GodCamController::SwitchToGodCam();
	///			break;
	///		// if "2" key pressed, switch back to last scene camera
	///		case AZUL_KEY::KEY_2:
	///			GodCamController::SwitchToLastUserCam();
	///			break;
	///		}
	/// }
	///	\endcode
	///
	///	\note You must include the "GodCamController.h" header to access the GodCam
	///
	///-------------------------------------------------------------------------------------------------
	static void SwitchToGodCam() { Instance().privSwitchToGodCam(); }

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void GodCamController::SwitchToLastUserCam()
	///
	/// \brief	Switches to last user camera.
	///
	/// When you are done using the God Cam, call \b SwitchToLastUserCam() to switch back to your old scene camera.
	///
	/// \par Example
	///		In the following example, the user has created a CameraController Game Object to manager their camera.
	///		They have set up key events to switch between the GodCam and their scene camera.
	///
	///	\code
	///	void CameraController::KeyPressed(AZUL_KEY k)
	/// {
	///		switch (k)
	///		{
	///		// if "1" key pressed, switch to GodCam
	///		case AZUL_KEY::KEY_1:
	///			GodCamController::SwitchToGodCam();
	///			break;
	///		// if "2" key pressed, switch back to last scene camera
	///		case AZUL_KEY::KEY_2:
	///			GodCamController::SwitchToLastUserCam();
	///			break;
	///		}
	/// }
	///	\endcode
	///
	///	\note You must include the "GodCamController.h" header to access the GodCam
	///
	///-------------------------------------------------------------------------------------------------
	static void SwitchToLastUserCam() { Instance().privSwitchToLastUserCam(); }
};

#endif GodCamController_
