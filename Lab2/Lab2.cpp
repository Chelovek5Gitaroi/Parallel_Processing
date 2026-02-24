#include <iostream>
#include <chrono>

#include <omp.h>

#include "ArgsPositions.h"
#include "MathFunctions.h"
#include "MessageBuilder.h"
#include "IntegralCalculator.h"

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

	uint32_t threadsNumber = static_cast<uint32_t>(atoi(argv[args::ARG_THREADS_NUMBER]));

	ntgrl::singleArgFunc function = mth::Math::getMathFunction(funcIndex);

	double totalIntegral = 0;

	double rectWidth = (right - left) / static_cast<double>(rects);

	double step = (right - left) / static_cast<double>(threadsNumber);

	double* x = new double[threadsNumber];

	x[0] = left;

	omp_set_num_threads(threadsNumber);

	for (int i = 1; i < threadsNumber; ++i)
	{
		x[i] = x[i - 1] + step;
	}

	double buf = 0;

	time_point<steady_clock> start = steady_clock::now();

	#pragma omp parallel for
		for (int i = 0; i < threadsNumber; ++i)
		{
			buf = ntgrl::IntegralCalculator::calcIntegral(function, x[i], x[i] + step, rectWidth);

			#pragma omp critical
			{
				totalIntegral += buf;
			}
		}

	time_point<steady_clock> finish = steady_clock::now();

	nanoseconds dur = std::chrono::duration_cast<nanoseconds>(finish - start);

	std::cout << msb::MessageBuilder::buildResultMessage(function, left, right, rects, totalIntegral, dur.count()) << "\n";

	delete[] x;
}