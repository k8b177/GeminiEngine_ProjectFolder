// ErrorMessage

#include "ErrorMessage.h"

#include "DebugOut.h"

ErrorMessage::ErrorMessage(std::string s, ErrorType t)
	:message(s), type(t)
{
	PrintError();
}

void ErrorMessage::PrintError()
{
	DebugMsg::out("\n------------------ERROR!------------------\n");
	DebugMsg::out(&message[0]);
	DebugMsg::out("\n------------------------------------------\n\n");

	if (type == ErrorType::Crash)
		exit(EXIT_FAILURE);
}