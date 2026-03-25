#include "MessageBuilder.h"

namespace msb
{
	std::string MessageBuilder::buildResultMessage(double (*func)(double), double left, double right, int rects, double integral, uint64_t nanoSeconds)
	{
		std::string result = "f(x) = " + mth::Math::funcToString(func) + "\nx0 = " + std::to_string(left) + ", xn = " + std::to_string(right) + "\nrects = " +
			std::to_string(rects) + "\nintegral = " + std::to_string(integral) + "\ntime duration: ";

		std::string totalNanoSeconds = "Total nanoseconds: " + std::to_string(nanoSeconds) + '\n';

		uint64_t microSeconds = nanoSeconds / 1000;

		uint64_t milliSeconds = microSeconds / 1000;

		uint64_t seconds = milliSeconds / 1000;

		uint64_t minutes = seconds / 60;

		seconds %= 60;

		milliSeconds %= 1000;

		microSeconds %= 1000;

		result += std::to_string(minutes) + "m, " + std::to_string(seconds) + "s, " + std::to_string(milliSeconds) + "ms, " +
			std::to_string(microSeconds) + "mcs, " + std::to_string(nanoSeconds % 1000) + "ns\n" + totalNanoSeconds;

		return result;
	}
}