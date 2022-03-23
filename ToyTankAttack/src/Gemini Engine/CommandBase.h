#ifndef CommandBase_
#define CommandBase_

class CommandBase
{
private:

public:
	// ---- BIG FOUR ---- //
	CommandBase() = default;
	CommandBase(const CommandBase&) = delete;
	CommandBase& operator= (const CommandBase&) = delete;
	virtual ~CommandBase() = default;


	virtual void Execute() = 0;
};

#endif CommandBase_