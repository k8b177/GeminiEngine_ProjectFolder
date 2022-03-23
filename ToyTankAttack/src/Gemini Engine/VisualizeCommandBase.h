#ifndef VisualizeCommandBase_
#define VisualizeCommandBase_

class VisualizeCommandBase
{
private:

public:
	// ---- BIG FOUR ---- //
	VisualizeCommandBase() = default;
	VisualizeCommandBase(const VisualizeCommandBase&) = delete;
	VisualizeCommandBase& operator= (const VisualizeCommandBase&) = delete;
	virtual ~VisualizeCommandBase() = default;


	virtual void Execute() = 0;
	virtual void Recycle() = 0;
};

#endif VisualizeCommandBase_