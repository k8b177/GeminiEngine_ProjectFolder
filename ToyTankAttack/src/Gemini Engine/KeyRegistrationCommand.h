#ifndef KeyRegistrationCommand_
#define KeyRegistrationCommand_

#include "CommandBase.h"
#include "KeyboardEventManager.h"
#include "Inputable.h"

class KeyRegistrationCommand : public CommandBase
{
private:
	Inputable* ptrIn;
	AZUL_KEY key;
	EVENT_TYPE e_type;
	Inputable::DataMapEntryRef in_mapEntryRef;

public:
	// ---- BIG FOUR ---- //
	KeyRegistrationCommand() = delete;
	KeyRegistrationCommand(const KeyRegistrationCommand&) = delete;
	KeyRegistrationCommand& operator= (const KeyRegistrationCommand&) = delete;
	~KeyRegistrationCommand() = default;

	KeyRegistrationCommand(Inputable* in, AZUL_KEY k, EVENT_TYPE e);

	void SetInRef(Inputable::DataMapEntryRef ref); 


	virtual void Execute() override;
};

#endif KeyRegistrationCommand_