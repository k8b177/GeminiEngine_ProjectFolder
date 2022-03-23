#ifndef Alarmable_
#define Alarmable_

#include "RegistrationStateEnum.h"
#include "AlarmableManager.h"

class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;

class Alarmable
{
	/// \cond
	friend class AlarmableAttorney;

private:
	struct RegistrationData // data needed for each alarm that this alarmable has
	{
		RegistrationState RegStateCurr; // current registration state

		AlarmRegistrationCommand* pRegistrationCmd; // pointer to instance of registration command
		AlarmDeregistrationCommand* pDeregistrationCmd; // pointer to instance of deregistration command

		AlarmableManager::TimeLineEntryRef pMyDeleteRef; // pointer to this object's iterator in AlarmableManager list
													   // used for fast delete in AlarmableManager
	};
	RegistrationData RegData[AlarmableManager::ALARM_NUMBER]; // array of all this alarmable's alarm data

	void SetDeleteRef(AlarmableManager::ALARM_ID id, AlarmableManager::TimeLineEntryRef ref); // only available to AlarmableManager
	AlarmableManager::TimeLineEntryRef GetDeleteRef(AlarmableManager::ALARM_ID id); // only available to AlarmableManager

	void AlarmRegistration(float t, AlarmableManager::ALARM_ID id); // inaccessible to user; user must use SubmitAlarmRegistration
	void AlarmDeregistration(AlarmableManager::ALARM_ID id); // inaccessible to user; user must use SubmitAlarmDeregistration

	void TriggerAlarm(AlarmableManager::ALARM_ID id);

public:
	// ---- BIG FOUR ---- //
	Alarmable();
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator= (const Alarmable&) = delete;
	virtual ~Alarmable();
	/// \endcond

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Alarmable::Alarm0()
	///
	/// \brief	The code that is called at time user specified \b Alarm0 to go off during Alarm Registration.
	/// 		
	/// See Alarmable::SubmitAlarmRegistration(float t, AlarmableManager::ALARM_ID id) for how to register an alarm.
	/// 	
	/// \par Example:
	/// 	 	
	/// \code
	/// void Frigate::Alarm0()
	/// {
	/// 	// When the alarm goes off, the Frigate will "become invisible"
	/// 	Drawable::SubmitDrawDeregistration(); // frigate will not draw anymore
	/// }
	/// \endcode
	///
	///-------------------------------------------------------------------------------------------------
	virtual void Alarm0() {};

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Alarmable::Alarm1()
	///
	/// \brief	The code that is called at time user specified \b Alarm1 to go off during Alarm Registration.
	/// 		
	/// See Alarmable::SubmitAlarmRegistration(float t, AlarmableManager::ALARM_ID id) for how to register an alarm.
	/// 
	/// \par Example:
	/// 	
	/// \code
	/// void Frigate::Alarm1()
	/// {
	/// 	// When the alarm goes off, the Frigate will "become invisible"
	/// 	Drawable::SubmitDrawDeregistration(); // frigate will not draw anymore
	/// }
	/// \endcode
	///
	///-------------------------------------------------------------------------------------------------
	virtual void Alarm1() {};

	///-------------------------------------------------------------------------------------------------
	/// \fn	virtual void Alarmable::Alarm2()
	///
	/// \brief	The code that is called at time user specified \b Alarm2 to go off during Alarm Registration.
	/// 		
	/// See Alarmable::SubmitAlarmRegistration(float t, AlarmableManager::ALARM_ID id) for how to register an alarm.
	/// 	
	/// \par Example:
	/// 	 	
	/// \code
	/// void Frigate::Alarm2()
	/// {
	/// 	// When the alarm goes off, the Frigate will "become invisible"
	/// 	Drawable::SubmitDrawDeregistration(); // frigate will not draw anymore
	/// }
	/// \endcode
	///
	///-------------------------------------------------------------------------------------------------
	virtual void Alarm2() {};

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Alarmable::SubmitAlarmRegistration(float t, AlarmableManager::ALARM_ID id);
	///
	/// \brief	Requests an Alarm to be registered.
	///
	/// Use when you want to set an alarm to trigger some time in the future.
	///
	/// \param 	t 	How many seconds in the future the alarm will go off.
	/// \param 	id	Which alarm should go off (ALARM_0, ALARM_1, or ALARM_2)
	/// 			
	/// \par Example:
	/// 	 
	/// \code
	/// Frigate::Frigate()
	/// {
	/// 	// Alarm0 will go off in 5 seconds
	/// 	Alarmable::SubmitAlarmRegistration(5.0f, AlarmableManager::ALARM_ID::ALARM_0);
	/// }
	/// \endcode 
	/// 			
	///-------------------------------------------------------------------------------------------------
	void SubmitAlarmRegistration(float t, AlarmableManager::ALARM_ID id);

	///-------------------------------------------------------------------------------------------------
	/// \fn	void Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id);
	///
	/// \brief	Requests an Alarm to be deregistered.
	/// 
	/// \param 	id	Which alarm should be deregistered (ALARM_0, ALARM_1, or ALARM_2)
	/// 		
	/// \par Example:
	///
	/// \code
	/// void Frigate_Input::KeyPressed(AZUL_KEY k)
	/// {
	///	// If the T Key is pressed, Alarm0 will deregister.
	/// 	if (k == AZUL_KEY::KEY_T)
	/// 		Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	/// }
	/// \endcode
	/// 				
	///-------------------------------------------------------------------------------------------------
	void SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id);

	
	float GetAlarmTime(AlarmableManager::ALARM_ID id);
	void SetAlarmTime(float timeOffset, AlarmableManager::ALARM_ID id);
};


#endif Alarmable_
