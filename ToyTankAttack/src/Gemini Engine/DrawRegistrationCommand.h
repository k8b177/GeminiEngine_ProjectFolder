#ifndef DrawRegistrationCommand_
#define DrawRegistrationCommand_

#include "CommandBase.h"

class Drawable;

class DrawRegistrationCommand : public CommandBase
{
private:
	Drawable* ptrDr;

public:
	// ---- BIG FOUR ---- //
	DrawRegistrationCommand() = delete;
	DrawRegistrationCommand(const DrawRegistrationCommand&) = delete;
	DrawRegistrationCommand& operator= (const DrawRegistrationCommand&) = delete;
	~DrawRegistrationCommand() = default;

	DrawRegistrationCommand(Drawable* dr);


	virtual void Execute() override;
};

#endif DrawRegistrationCommand_