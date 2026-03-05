#include <iostream>
#include <chrono>


#include "MathFunctions.h"
#include "IntegralCalculator.h"
#include "MessageBuilder.h"
#include "ArgsPositions.h"

using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::nanoseconds;

int main(int argc, char** argv)
{
	double left = static_cast<double>(atof(argv[args::ARG_LEFT]));
	double right = static_cast<double>(atof(argv[args::ARG_RIGHT]));

	uint64_t rects = static_cast<uint64_t>(std::stoull(argv[args::ARG_RECTS]));

	uint32_t funcIndex = static_cast<uint32_t>(atoi(argv[args::ARG_FUNC]));

	double rectWidth = (right - left) / static_cast<double>(rects);

	ntgrl::singleArgFunc function = mth::Math::getMathFunction(funcIndex);

	uint32_t itersCount = static_cast<uint32_t>(atoi(argv[args::ARG_ITERATIONS_COUNT]));

	for (uint32_t i = 0; i < itersCount; ++i)
	{
		time_point<steady_clock> start = steady_clock::now();

		double integral = ntgrl::IntegralCalculator::calcIntegral(function, left, right, rectWidth);

		time_point<steady_clock> finish = steady_clock::now();

		nanoseconds dur = std::chrono::duration_cast<nanoseconds>(finish - start);

		std::cout << msb::MessageBuilder::buildResultMessage(function, left, right, rects, integral, dur.count()) << "\n\n";
	}

	return 0;
}


