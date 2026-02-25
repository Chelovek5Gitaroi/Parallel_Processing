using System;

namespace RectangleIntegralCs
{
  public class IntegralCalculator
  {
    public static double CalcIntegralRectangle(dSingleArgFunc func, double left, double right, double rectWidth)
    {
      double result = 0;

      for (double x = left; x < right - rectWidth / 2.0; x += rectWidth)
      {
        try
        {
          result += func(x) * rectWidth;
        }
        catch (DivideByZeroException)
        {
        }
      }

      return result;
    }

  }
}
