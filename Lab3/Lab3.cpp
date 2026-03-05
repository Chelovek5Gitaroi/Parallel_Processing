#include <mpi.h>
#include <iostream>
#include <chrono>

#include "ArgsPositions.h"
#include "IntegralCalculator.h"
#include "MathFunctions.h"
#include "MessageBuilder.h"

using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::nanoseconds;

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);

	int pid;
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	int threadsNumber;
	MPI_Comm_size(MPI_COMM_WORLD, &threadsNumber);

	double left = static_cast<double>(atof(argv[args::ARG_LEFT]));
	double right = static_cast<double>(atof(argv[args::ARG_RIGHT]));

	uint64_t rects = static_cast<uint64_t>(std::stoull(argv[args::ARG_RECTS]));

	double rectWidth = (right - left) / static_cast<double>(rects);

	double step = (right - left) / static_cast<double>(threadsNumber);

	double x = left + step * pid;

	time_point<steady_clock> start;

	uint32_t funcIndex = static_cast<uint32_t>(atoi(argv[args::ARG_FUNC]));

	mth::singleArgFunc func = mth::Math::getMathFunction(funcIndex);

	if (pid == 0)
	{
		start = steady_clock::now();
	}

	MPI_Barrier(MPI_COMM_WORLD);

	double integr = ntgrl::IntegralCalculator::calcIntegral(func, x, x + step, rectWidth);

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Request req;

	if (pid < threadsNumber - 1)
	{
		double buf = 0;

		MPI_Status status;
		MPI_Recv(&buf, 1, MPI_DOUBLE, pid + 1, pid + 1, MPI_COMM_WORLD, &status);

		integr += buf;
	}

	if (pid > 0)
	{
		MPI_Send(&integr, 1, MPI_DOUBLE, pid - 1, pid, MPI_COMM_WORLD);

		MPI_Barrier(MPI_COMM_WORLD);
	}
	else
	{
		MPI_Barrier(MPI_COMM_WORLD);
		time_point<steady_clock> finish;

		finish = steady_clock::now();
		nanoseconds dur = std::chrono::duration_cast<nanoseconds>(finish - start);

		std::cout << msb::MessageBuilder::buildResultMessage(func, left, right, rects, integr, dur.count()) << "\n";
	}

	MPI_Finalize();

	return 0;
}