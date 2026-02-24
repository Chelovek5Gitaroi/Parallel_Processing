#ifndef MATH_FUNCTIONS
#define MATH_FUNCTIONS

#include <cmath>

#include "DivideByZeroException.h"

#include <string>

namespace mth
{
	typedef double (*singleArgFunc)(double);

	class Math final
	{
	public:
		static double funcX2pX(double x);

		static double funcX3mX2pX(double x);

		static double funcX2sinX(double x);

		static double funcMx2sinX(double x);

		static double funcX2sinXp4xDxPcosX(double x);

		static std::string funcToString(double (*func)(double));

		static singleArgFunc getMathFunction(uint32_t index);
	private:
		Math();
		~Math();

		static const double ABOUT_ZERO;
	};
}

#endif