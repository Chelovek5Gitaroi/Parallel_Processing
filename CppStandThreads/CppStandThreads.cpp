#include <iostream>

#include <chrono>
#include <thread>
#include <vector>
#include <mutex>

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
	uint32_t multipliesCount = static_cast<uint32_t>(atoi(argv[args::ARG_THREADS_MULTIPLY_COUNT]));

	for (uint32_t k = 0, threadsCount = args::START_TREADS_NUMBER; k <= multipliesCount; ++k, threadsCount *= 2)
	{
		std::cout << "Threads count: " << threadsCount << "\n";
		
		double rectWidth = (right - left) / static_cast<double>(rects);

		double step = (right - left) / static_cast<double>(threadsCount);

		for (int i = 0; i < itersCount; ++i)
		{
			double result = 0;

			std::mutex sync;

			double* x = new double[threadsCount];

			x[0] = left;

			for (int i = 1; i < threadsCount; ++i)
			{
				x[i] = x[i - 1] + step;
			}

			std::vector<std::thread> threads;

			time_point<steady_clock> start = steady_clock::now();

			for (int i = 0; i < threadsCount; ++i)
			{
				threads.push_back(std::thread([&result, &sync](double x, ntgrl::singleArgFunc func, double step, double rectWidth)
					{
						double buf = ntgrl::IntegralCalculator::calcIntegral(func, x, x + step, rectWidth);

						sync.lock();
						result += buf;
						sync.unlock();

					}, x[i], function, step, rectWidth));
			}

			for (auto iter = threads.begin(); iter != threads.end(); ++iter)
			{
				iter->join();
			}

			time_point<steady_clock> finish = steady_clock::now();

			nanoseconds dur = std::chrono::duration_cast<nanoseconds>(finish - start);

			std::cout << msb::MessageBuilder::buildResultMessage(function, left, right, rects, result, dur.count()) << "\n\n";

			delete[] x;
		}
	}

	return 0;
}