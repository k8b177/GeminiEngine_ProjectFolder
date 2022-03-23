#ifndef UpdateRegistrationCommand_
#define UpdateRegistrationCommand_

#include "CommandBase.h"

class Updatable;

class UpdateRegistrationCommand : public CommandBase
{
private:
	Updatable* ptrUp;

public:
	// ---- BIG FOUR ---- //
	UpdateRegistrationCommand() = delete;
	UpdateRegistrationCommand(const UpdateRegistrationCommand&) = delete;
	UpdateRegistrationCommand& operator= (const UpdateRegistrationCommand&) = delete;
	~UpdateRegistrationCommand() = default;

	UpdateRegistrationCommand(Updatable* up);


	virtual void Execute() override;
};

#endif UpdateRegistrationCommand_