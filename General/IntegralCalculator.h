#ifndef INTEGRAL_CALCULATOR
#define INTEGRAL_CALCULATOR

#include <cstdint>

#include "DivideByZeroException.h"

namespace ntgrl
{
	typedef double (*singleArgFunc)(double);

	class IntegralCalculator final
	{
	public:
		static double calcIntegral(singleArgFunc func, double leftBorder, double rightBorder, double rectWidth);

	private:
		IntegralCalculator() {}
		~IntegralCalculator() {}

		//static const double ABOUT_ZERO;// = 0.001;
	};
}

#endif
