#pragma once

#include <string>
#include <fstream>

#include <CL/cl.hpp>

#include <iostream>

class ClBuilder
{
private:
	static std::string readClProgram(const std::string& programFileName);

public:
	static cl::Device getDevice(cl::Platform& platform, size_t index);

	static cl::Platform getPlatform(size_t index);

	static std::string getFunctionName(int32_t index);

	static cl::Program buildProgram(const std::string& fileName, const cl::Device& device, cl::Context& context, cl_int workGroupSize, int32_t funcIndex);

	static cl_float invokeKernel(cl::CommandQueue& queue, cl::Kernel& kernel, cl::Buffer& left, cl::Buffer& right,
		cl_float rectWidth, cl::Buffer& resultBuf, size_t bufferSize, std::vector<cl_float>& resultVec, int workGroupSize);
};

