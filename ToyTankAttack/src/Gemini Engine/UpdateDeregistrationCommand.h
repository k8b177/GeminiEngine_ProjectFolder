#ifndef UpdateDeregistrationCommand_
#define UpdateDeregistrationCommand_

#include "CommandBase.h"

class Updatable;

class UpdateDeregistrationCommand : public CommandBase
{
private:
	Updatable* ptrUp;

public:
	// ---- BIG FOUR ---- //
	UpdateDeregistrationCommand() = delete;
	UpdateDeregistrationCommand(const UpdateDeregistrationCommand&) = delete;
	UpdateDeregistrationCommand& operator= (const UpdateDeregistrationCommand&) = delete;
	~UpdateDeregistrationCommand() = default;

	UpdateDeregistrationCommand(Updatable* ptrUp);

	virtual void Execute() override;
};

#endif UpdateDeregistrationCommand_