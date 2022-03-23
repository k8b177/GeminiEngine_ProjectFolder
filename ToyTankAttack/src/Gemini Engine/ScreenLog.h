#ifndef ScreenLog_
#define ScreenLog_

#include <list>
#include "SpriteStringPool.h"

class SpriteFont;

class ScreenLog
{
	/// \cond
	friend class ScreenLogAttorney;
private:
	static ScreenLog* ptrInstance;
	static ScreenLog& Instance();

	static void Delete();
	static void Render() { Instance().privRender(); }

	void privRender();

	// ---- BIG FOUR ---- //
	ScreenLog();
	ScreenLog(const ScreenLog&) = delete;
	ScreenLog& operator= (const ScreenLog&) = delete;
	~ScreenLog() = default;

	// ---- PRIV FIELDS ---- //
	float anchorX;
	float anchorY;
	static char DebugBuff[256];
	SpriteFont* font;

	// sprite string pool
	SpriteStringPool mySpriteStringPool;

	using Message = std::string;
	using MessageCollection = std::list<Message>;
	MessageCollection messages;
	/// \endcond

public:

	///-------------------------------------------------------------------------------------------------
	/// \fn	static void ScreenLog::Add(char* A, ...);
	///
	/// \brief	Adds a line of text to the ScreenLog on the screen.
	/// 		
	/// Format the arguments as you would format a printf statement.
	///
	/// \param [in,out]	A  	The c_string of your debug statement.
	/// \param 		   	...	Variable arguments providing additional information.
	/// 					
	///-------------------------------------------------------------------------------------------------
	static void Add(char* A, ...);

};

#endif ScreenLog_
