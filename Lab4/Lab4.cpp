#pragma warning(disable : 4996)

#include <vector>
#include <iostream>

#include "ClBuilder.h"

#include <chrono>

#include "ArgsPositions.h"
#include "IntegralCalculator.h"
#include "MessageBuilder.h"

using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::nanoseconds;

int main(int argc, char** argv)
{
	cl::Platform platform = ClBuilder::getPlatform(0);

	cl::Device device = ClBuilder::getDevice(platform, 0);

	cl_int workGroupSize = static_cast<cl_int>(device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>());
	size_t computeUnits = device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();

	std::cout << "Max work group size: " << workGroupSize << "\nCompute units: " << computeUnits << "\n";

	cl::Context context(device);
	cl::CommandQueue queue(context, device);

	cl_float left = static_cast<cl_float>(atof(argv[args::ARG_LEFT]));
	cl_float right = static_cast<cl_float>(atof(argv[args::ARG_RIGHT]));

	uint64_t rects = static_cast<uint64_t>(std::stoull(argv[args::ARG_RECTS]));


	uint32_t funcIndex = static_cast<uint32_t>(atoi(argv[args::ARG_FUNC]));

	cl_float rectWidth = (right - left) / static_cast<cl_float>(rects);

	uint32_t itersCount = static_cast<uint32_t>(atoi(argv[args::ARG_ITERATIONS_COUNT]));

	cl::Program program = ClBuilder::buildProgram("Kernel.cl", device, context, workGroupSize, funcIndex);

	std::cout << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);

	ntgrl::singleArgFunc function = mth::Math::getMathFunction(funcIndex);

	int bufLen = (rects / workGroupSize) * workGroupSize;

	if (rects % workGroupSize)
	{
		bufLen += workGroupSize;
	}

	std::vector<cl_float> vleft(bufLen, 0);
	std::vector<cl_float> vright(bufLen, 0);
	std::vector<cl_float> vresult(bufLen, 0);

	for (int i = 0; i < rects; ++i)
	{
		vleft[i] = (left + i * rectWidth);
		vright[i] = (vleft[i] + rectWidth);
	}
	
	cl::Buffer bufLeft(context, vleft.begin(), vleft.end(), true);
	cl::Buffer bufRight(context, vright.begin(), vright.end(), true);
	cl::Buffer bufResult(context, vresult.begin(), vresult.end(), false);

	cl::Kernel kernel(program, "calcIntegral");

	for (int i = 0; i < itersCount; ++i)
	{
		time_point<steady_clock> start = steady_clock::now();

		cl_float result = ClBuilder::invokeKernel(queue, kernel, bufLeft, bufRight, rectWidth, bufResult, vresult.size(), vresult, workGroupSize);

		time_point<steady_clock> finish = steady_clock::now();

		nanoseconds dur = std::chrono::duration_cast<nanoseconds>(finish - start);

		std::cout << msb::MessageBuilder::buildResultMessage(function, left, right, rects, result, dur.count()) << "\n\n";
	}
	
	return 0;
}