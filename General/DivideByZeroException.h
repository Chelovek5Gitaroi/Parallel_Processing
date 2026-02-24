#ifndef DIVIDE_BY_ZERO_EXCEPTION
#define DIVIDE_BY_ZERO_EXCEPTION

#include <exception>

namespace expt
{
	class DivideByZeroException : public std::exception
	{
	public:
		DivideByZeroException() noexcept;

		inline const char* what() const noexcept override;
	private:
		static const char* ERROR_MESSAGE;
	};
}

#endif
