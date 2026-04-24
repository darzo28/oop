#include "CUrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string& error_message)
	: std::invalid_argument(error_message)
{
}