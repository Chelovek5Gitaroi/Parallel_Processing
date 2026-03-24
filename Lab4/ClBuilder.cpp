#include "ClBuilder.h"

std::string ClBuilder::readClProgram(const std::string& programFileName)
{
	std::ifstream fin(programFileName);

	return std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
}

cl::Program ClBuilder::buildProgram(const std::string& fileName, cl::Context& context)
{
	const std::string code = readClProgram(fileName);

	cl::Program program(context, code, true);

	return program;
}

cl::Device ClBuilder::getDevice(cl::Platform& platform, size_t index)
{
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

	return devices[index];
}

cl::Platform ClBuilder::getPlatform(size_t index)
{
	std::vector<cl::Platform> platforms;

	cl::Platform::get(&platforms);

	return platforms[index];
}

cl_float ClBuilder::invokeKernel(cl::CommandQueue& queue, cl::Kernel& kernel, cl::Buffer& left, cl::Buffer& right,
	cl_float rectWidth, cl::Buffer& resultBuf, size_t bufferSize, std::vector<cl_float>& resultVec)
{
	cl_int err;

	err = kernel.setArg(0, left);
	err = kernel.setArg(1, right);
	err = kernel.setArg(2, rectWidth);
	err = kernel.setArg(3, resultBuf);

	cl::NDRange ndRange(bufferSize);

	err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, ndRange, cl::NullRange);

	queue.finish();

	err = queue.enqueueReadBuffer(resultBuf, CL_TRUE, 0, sizeof(cl_float) * bufferSize, resultVec.data());

	cl_float result = 0;

	for (size_t i = 0; i < resultVec.size(); ++i)
	{
		result += resultVec[i];
	}

	return result;
}