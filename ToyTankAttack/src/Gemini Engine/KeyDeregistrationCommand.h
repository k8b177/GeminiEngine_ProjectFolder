#ifndef KeyDeregistrationCommand_
#define KeyDeregistrationCommand_

#include "CommandBase.h"
#include "KeyboardEventManager.h"
#include "Inputable.h"

class KeyDeregistrationCommand : public CommandBase
{
private:
	Inputable* ptrIn;
	AZUL_KEY key;
	EVENT_TYPE e_type;
	Inputable::DataMapEntryRef in_mapEntryRef;

public:
	// ---- BIG FOUR ---- //
	KeyDeregistrationCommand() = delete;
	KeyDeregistrationCommand(const KeyDeregistrationCommand&) = delete;
	KeyDeregistrationCommand& operator= (const KeyDeregistrationCommand&) = delete;
	~KeyDeregistrationCommand() = default;

	KeyDeregistrationCommand(Inputable* in, AZUL_KEY k, EVENT_TYPE e);

	void SetInRef(Inputable::DataMapEntryRef ref);

	virtual void Execute() override;
};

#endif KeyDeregistrationCommand_