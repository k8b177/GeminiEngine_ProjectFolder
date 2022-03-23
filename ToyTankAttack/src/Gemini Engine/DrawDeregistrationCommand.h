#ifndef DrawDeregistrationCommand_
#define DrawDeregistrationCommand_

#include "CommandBase.h"

class Drawable;

class DrawDeregistrationCommand : public CommandBase
{
private:
	Drawable* ptrDr;

public:
	// ---- BIG FOUR ---- //
	DrawDeregistrationCommand() = delete;
	DrawDeregistrationCommand(const DrawDeregistrationCommand&) = delete;
	DrawDeregistrationCommand& operator= (const DrawDeregistrationCommand&) = delete;
	~DrawDeregistrationCommand() = default;

	DrawDeregistrationCommand(Drawable* dr);


	virtual void Execute() override;
};

#endif DrawDeregistrationCommand_