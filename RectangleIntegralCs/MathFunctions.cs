using System;

namespace RectangleIntegralCs
{
  public delegate double dSingleArgFunc(double par);

  public class MathFunctions
  {
    private const double ABOUT_ZERO = 0.0000001;

    public static double FuncX2pX(double parX)
    {
      return Math.Pow(parX, 2) + parX;
    }

    public static double FuncX3mX2pX(double parX)
    {
      return Math.Pow(parX, 3) - Math.Pow(parX, 2) + parX;
    }

    public static double FuncX2sinX(double parX)
    {
      return Math.Pow(parX, 2) * Math.Sin(parX);
    }

    public static double FuncMx2sinX(double parX)
    {
      return (-1.0) * FuncX2sinX(parX);
    }

    public static double FuncX2sinXp4xDxPcosX(double parX)
    {
      double denominator = parX + Math.Cos(parX);

      if (Math.Abs(denominator) <= ABOUT_ZERO)
      {
        throw new DivideByZeroException();
      }

      return (Math.Sin(parX) * Math.Pow(parX, 2) + 4 * parX) / denominator;
    }

    public static dSingleArgFunc GetFunction(int index)
    {
      dSingleArgFunc result = null;

      switch (index)
      {
        case 1:
          result = FuncX2pX;
          break;
        case 2:
          result = FuncX3mX2pX;
          break;
        case 3:
          result = FuncX2sinX;
          break;
        case 4:
          result = FuncMx2sinX;
          break;
        case 5:
          result = FuncX2sinXp4xDxPcosX;
          break;
        default:
          break;
      }

      return result;
    }

    public static string FunctionToString(dSingleArgFunc func)
    {
      string result = "";

      if (func == FuncX2pX)
      {
        result = "x^2 + x";
      }
      else if (func == FuncX3mX2pX)
      {
        result = "x^3 - x^2 + x";
      }
      else if (func == FuncX2sinX)
      {
        result = "x^2 * sin(x)";
      }
      else if (func == FuncMx2sinX)
      {
        result = "-x^2 * sin(x)";
      }
      else if (func == FuncX2sinXp4xDxPcosX)
      {
        result = "(x^2 * sin(x) + 4x) / (x + cos(x))";
      }

      return result;
    }
  }
}
