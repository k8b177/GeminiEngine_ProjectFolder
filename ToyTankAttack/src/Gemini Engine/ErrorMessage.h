// Error Message
// Katherine Burnett, January 2022

#include "ErrorType.h"

#ifndef _ErrorMessage
#define _ErrorMessage

class ErrorMessage 
{
public:
	// ---- BIG FOUR ---- //
	ErrorMessage() = delete;
	ErrorMessage(const ErrorMessage&) = default;
	ErrorMessage& operator= (const ErrorMessage&) = default;
	~ErrorMessage() = default;

	ErrorMessage(std::string s, ErrorType t);

private:
	std::string message;
	ErrorType type;

	void PrintError();
};

#endif _ErrorMessage