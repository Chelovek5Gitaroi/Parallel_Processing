#include "MathFunctions.h"

namespace mth
{
	Math::Math() {}
	Math::~Math() {}

	const double Math::ABOUT_ZERO = 0.0000001;

	double Math::funcX2pX(double x)
	{
		return std::pow(x, 2) + x;
	}

	double Math::funcX3mX2pX(double x)
	{
		return  std::pow(x, 3) - std::pow(x, 2) + x;
	}

	double Math::funcX2sinX(double x)
	{
		return std::pow(x, 2) * sin(x);
	}

	double Math::funcMx2sinX(double x)
	{
		return funcX2sinX(x) * (-1.0);
	}

	double Math::funcX2sinXp4xDxPcosX(double x)
	{
		double denominator = x + cos(x);

		if (std::abs(denominator) <= ABOUT_ZERO)
		{
			throw expt::DivideByZeroException();
		}

		return (sin(x) * std::pow(x, 2) + 4 * x) / denominator;
	}

	std::string Math::funcToString(double (*func)(double))
	{
		std::string result = "";

		if (func == funcX2pX)
		{
			result = "x^2 + x";
		}
		else if (func == funcX3mX2pX)
		{
			result = "x^3 - x^2 + x";
		}
		else if (func == funcX2sinX)
		{
			result = "x^2 * sin(x)";
		}
		else if (func == funcMx2sinX)
		{
			result = "-x^2 * sin(x)";
		}
		else if (func == funcX2sinXp4xDxPcosX)
		{
			result = "(x^2 * sin(x) + 4x) / (x + cos(x))";
		}

		return result;
	}

	singleArgFunc Math::getMathFunction(uint32_t index)
	{
		double (*result)(double) = nullptr;

		switch (index)
		{
		case 1:
			result = funcX2pX;
			break;
		case 2:
			result = funcX2sinX;
			break;
		case 3:
			result = funcX3mX2pX;
			break;
		case 4:
			result = funcMx2sinX;
			break;
		case 5:
			result = funcX2sinXp4xDxPcosX;
			break;
		default:
			result = funcX2pX;
			break;
		}
		
		return result;
	}
}