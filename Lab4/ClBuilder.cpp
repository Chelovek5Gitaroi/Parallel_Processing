#include "ClBuilder.h"

std::string ClBuilder::readClProgram(const std::string& programFileName)
{
	std::ifstream fin(programFileName);

	return std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
}

std::string ClBuilder::getFunctionName(int32_t index)
{
	switch (index)
	{
	case 1:
		return "funcX2pX";
	case 2:
		return "funcX3mX2pX";
	case 3:
		return "funcX2sinX";
	case 4:
		return "funcMx2sinX";
	case 5:
		return "funcX2sinXp4xDxPcosX";
	default:
		return "funcX2pX";
	}
}

cl::Program ClBuilder::buildProgram(const std::string& fileName, const cl::Device& device, cl::Context& context, cl_int workGroupSize, int32_t funcIndex)
{
	const std::string fileCode = readClProgram(fileName);

	const std::string sizeMacro = "#define SIZE " + std::to_string(workGroupSize) + "\n";

	const std::string funcMacro = "#define FUNC(x) " + getFunctionName(funcIndex) + "(x)\n";

	const std::string code = sizeMacro + funcMacro + fileCode;

	//std::cout << code << "\n";

	cl::Program program(context, code);

	program.build();


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
	cl_float rectWidth, cl::Buffer& resultBuf, size_t bufferSize, std::vector<cl_float>& resultVec, int workGroupSize)
{
	cl_int err = 0;

	err = kernel.setArg(0, left);
	err = kernel.setArg(1, right);
	err = kernel.setArg(2, rectWidth);
	err = kernel.setArg(3, resultBuf);

	cl::NDRange ndRange(bufferSize);

	cl::NDRange groupSize(workGroupSize);

	err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, ndRange, groupSize);

	if (err)
	{
		std::cout << "Enquing failed " << err << "\n";
	}

	queue.finish();

	err = queue.enqueueReadBuffer(resultBuf, CL_TRUE, 0, sizeof(cl_float) * bufferSize, resultVec.data());

	if (err)
	{
		std::cout << "Reading failed " << err << "\n";
	}

	int groupsCount = bufferSize / workGroupSize;

	cl_float result = 0;

	for (size_t i = 0; i < groupsCount; ++i)
	{
		result += resultVec[i];
	}

	return result;
}