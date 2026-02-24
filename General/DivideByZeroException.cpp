#include "DivideByZeroException.h"

namespace expt
{
	DivideByZeroException::DivideByZeroException() noexcept
	{
	}

	const char* DivideByZeroException::what() const noexcept
	{
		return ERROR_MESSAGE;
	}

	const char* DivideByZeroException::ERROR_MESSAGE = "Dividing by zero\n";
}