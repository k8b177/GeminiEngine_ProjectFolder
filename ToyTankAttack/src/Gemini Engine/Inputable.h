#ifndef Inputable_
#define Inputable_

#include "RegistrationStateEnum.h"
#include "SingleKeyEventManager.h"
#include "EVENT_TYPEEnum.h"
#include <map>

class KeyRegistrationCommand;
class KeyDeregistrationCommand;

class Inputable
{
	/// \cond
	friend class InputableAttorney;

private:
	struct RegistrationData;
	using DataMapEntry = std::pair<AZUL_KEY, RegistrationData*>; // shortcut for key, Registration Data pair
	using DataMap = std::map<AZUL_KEY, RegistrationData*>; // shortcut for DataMap type

public:
	using DataMapEntryRef = DataMap::iterator; // shortcut for iterator in DataMap

private:
	struct RegistrationData // data needed for each keyregistration that this inputable has
	{
		RegistrationState RegStateCurr; // current registration state

		KeyRegistrationCommand* pRegistrationCmd; // pointer to instance of registration command
		KeyDeregistrationCommand* pDeregistrationCmd; // pointer to instance of deregistration command

		SingleKeyEventManager::InputableCollectionRef pMyDeleteRef; // pointer to this object's iterator in KeyboardEventManager map
														   // used for fast delete in KeyboardEventManager

		RegistrationData(Inputable* in, AZUL_KEY k, EVENT_TYPE e);
		~RegistrationData();
	};



	DataMap PressDataMap; // map of keys to registration data for KEY_PRESSES
	DataMap ReleaseDataMap; // map of keys to registration data for KEY_RELEASES



	void SetDeleteRef(AZUL_KEY k, EVENT_TYPE e, SingleKeyEventManager::InputableCollectionRef sk_ref); // only available to SingleKeyEventManager
	SingleKeyEventManager::InputableCollectionRef GetDeleteRef(AZUL_KEY k, EVENT_TYPE e); // only available to DrawableManager
	
	// virtual void Draw() {}; // only available to DrawableManager


	void SceneRegistration(DataMapEntryRef ref, AZUL_KEY k, EVENT_TYPE e); // inaccessible to user; user must use SubmitKeyRegistration()
	void SceneDeregistration(DataMapEntryRef ref, AZUL_KEY k, EVENT_TYPE e); // inaccessible to user; user must use SubmitKeyDeregistration()
	/// \endcond

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Inputable::KeyPressed(AZUL_KEY k)
	///
	/// \brief	Called when a key press happens for a key that the GameObject registered to watch for.
	///
	/// \param 	k	The AZUL_KEY that was pressed.
	/// 			
	/// \par Example:
	///		\code
	///		void Frigate::KeyPressed(AZUL_KEY k)
	///		{
	///			// When the T key is pressed, the message will print
	///			if (k == AZUL_KEY::KEY_T)
	///				DebugMsg::out("Frigate: T Key Pressed\n");
	///		}
	///		\endcode
	/// 			
	/// \note
	/// 	When Inputable::KeyPressed(AZUL_KEY k) is called,
	///		GeminiEngine passes back the key as a parameter.
	///		So, it is on the user to check which key this is and respond appropriately.
	///		(Suggestion: use \b if/elseif logic or a \b switch statement) 
	/// 			
	///------------------------------------------------------------------------------------------------
	virtual void KeyPressed(AZUL_KEY k) { k; }; // only available to SK Manager;

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Inputable::KeyReleased(AZUL_KEY k)
	///
	/// \brief	Called when a key release happens for a key that the GameObject registered to watch for.
	///
	/// \param 	k	The AZUL_KEY that was released.
	/// 			
	/// \par Example:
	///		\code
	///		void Frigate::KeyReleased(AZUL_KEY k)
	///		{
	///			// When the T key is released, the message will print
	///			if (k == AZUL_KEY::KEY_T)
	///				DebugMsg::out("Frigate: T Key Released\n");
	///		}
	///		\endcode
	/// 			
	/// \note
	/// 	When Inputable::KeyReleased(AZUL_KEY k) is called,
	///		GeminiEngine passes back the key as a parameter.
	///		So, it is on the user to check which key this is and respond appropriately.
	///		(Suggestion: use \b if/elseif logic or a \b switch statement) 
	/// 			
	///-----------------------------------------------------------------------------------------------
	virtual void KeyReleased(AZUL_KEY k) { k; }; // only available to SKManager;

public:
	/// \cond
	// ---- BIG FOUR ---- //
	Inputable() = default;
	Inputable(const Inputable&) = delete;
	Inputable& operator= (const Inputable&) = delete;
	virtual ~Inputable();
	/// \endcond

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Inputable::SubmitKeyRegistration(AZUL_KEY k, EVENT_TYPE e);
	///
	/// \brief	Requests a Key, KeyEvent pair to be registered.
	/// 		
	/// \param 	k	The AZUL_KEY that this object wants to watch.
	/// \param 	e	What event this object cares about (EVENT_TYPE::KEY_PRESS or EVENT_TYPE::KEY_RELEASE).
	/// 		
	/// \par Example:
	/// 	\code
	///		Frigate::Frigate()
	///		 {
	///			// Submit for Key Registration
	///			// T, Press
	///			SubmitKeyRegistration(AZUL_KEY::KEY_T, EVENT_TYPE::KEY_PRESS);
	///			// T, Release
	///			SubmitKeyRegistration(AZUL_KEY::KEY_T, EVENT_TYPE::KEY_RELEASE);
	///		 }
	///		\endcode
	///								
	///-------------------------------------------------------------------------------------------------
	void SubmitKeyRegistration(AZUL_KEY k, EVENT_TYPE e);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Inputable::SubmitKeyDeregistration(AZUL_KEY k, EVENT_TYPE e);
	///
	/// \brief	Requests a Key, KeyEvent pair to be deregistered.
	/// 		
	/// \param 	k	The AZUL_KEY that this object no longer wants to watch.
	/// \param 	e	What event this object no longer cares about (EVENT_TYPE::KEY_PRESS or EVENT_TYPE::KEY_RELEASE).
	///
	/// \par Example:
	/// 	 
	/// 	\code
	///		void Frigate::Alarm0(AZUL_KEY k)
	///		{
	///			// Submit for Key Deregistration
	///			// T, Press
	///			SubmitKeyDeregistration(AZUL_KEY::KEY_T, EVENT_TYPE::KEY_PRESS);
	///			// T, Release
	///			SubmitKeyDeregistration(AZUL_KEY::KEY_T, EVENT_TYPE::KEY_RELEASE);
	///		}
	///		\endcode
	///		
	///-------------------------------------------------------------------------------------------------
	void SubmitKeyDeregistration(AZUL_KEY k, EVENT_TYPE e);


};


#endif Inputable_
