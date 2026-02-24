#ifndef MESSAGE_BUILDER
#define MESSAGE_BUILDER

#include <string>

#include "MathFunctions.h"

namespace msb
{
	class MessageBuilder final
	{
	public:
		static std::string buildResultMessage(double (*func)(double), double left, double right, int rects, double integral, uint64_t nanoSeconds);

	private:
		MessageBuilder() {}

		~MessageBuilder() {}
	};
}

#endif