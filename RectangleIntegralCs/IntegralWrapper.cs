
namespace RectangleIntegralCs
{
  public class IntegralWrapper
  {
    private dSingleArgFunc _intFunc;

    private double _leftX;

    private double _rightX;

    private double _rectWidth;

    private double _result;

    public IntegralWrapper(dSingleArgFunc parFunc, double parLeft, double parRight, double parRectWidth)
    {
      _intFunc = parFunc;
      _leftX = parLeft;
      _rightX = parRight;
      _rectWidth = parRectWidth;
    }

    public double GetResult()
    {
      return _result;
    }

    public void CalcIntegral()
    {
      _result = IntegralCalculator.CalcIntegralRectangle(_intFunc, _leftX, _rightX, _rectWidth);
    }
  }
}
