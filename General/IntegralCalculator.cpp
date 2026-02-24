#include "IntegralCalculator.h"

namespace ntgrl
{
	double IntegralCalculator::calcIntegral(singleArgFunc func, double leftBorder, double rightBorder, double rectWidth)
	{
		double result = 0;

		for (double x = leftBorder; x < rightBorder - rectWidth / 2; x += rectWidth)
		{
			try
			{
				result += func(x) * rectWidth;
			}
			catch (expt::DivideByZeroException& ex)
			{
				//result += func(x + ABOUT_ZERO) * rectWidth;
			}
		}

		return result;
	}

	//const double IntegralCalculator::ABOUT_ZERO = 0.0001;
}