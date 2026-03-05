
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using System;

namespace RectangleIntegralCs
{
  public class Program
  {
    const int ARG_LEFT = 0;
    const int ARG_RIGHT = 1;
    const int ARG_RECTS = 2;
    const int ARG_FUNC = 3;
    const int ARG_ITERS = 4;

    const int ARG_THREADS_MULTIPLY_COUNT = 5;

    const int THREADS_COUNT_START = 2;

    static void Main(string[] args)
    {
      double left = double.Parse(args[ARG_LEFT]);
      double right = double.Parse(args[ARG_RIGHT]);

      int rects = int.Parse(args[ARG_RECTS]);

      double rectWidth = (right - left) / rects;

      dSingleArgFunc func = MathFunctions.GetFunction(int.Parse(args[ARG_FUNC]));

      int itersCount = int.Parse(args[ARG_ITERS]);

      for (int k = 0, threadsCount = THREADS_COUNT_START; k < itersCount; ++k, threadsCount *= 2)
      {
        double step = (right - left) / threadsCount;

        double[] x = new double[threadsCount];

        x[0] = left;

        for (int i = 1; i < threadsCount; i++)
        {
          x[i] = x[i - 1] + step;
        }

        Stopwatch sw = new Stopwatch();

        List<Thread> threads = new List<Thread>();
        List<IntegralWrapper> wrappers = new List<IntegralWrapper>();

        for (int i = 0; i < threadsCount; ++i)
        {
          wrappers.Add(new IntegralWrapper(func, x[i], x[i] + step, rectWidth));
          threads.Add(new Thread(wrappers[i].CalcIntegral));
        }

        sw.Start();

        for (int i = 0; i < threadsCount; ++i)
        {
          threads[i].Start();
        }

        double integral = 0;

        for (int i = 0; i < threadsCount; ++i)
        {
          threads[i].Join();
          integral += wrappers[i].GetResult();
        }

        sw.Stop();


        Console.WriteLine($"Left: {left}\n" +
          $"Right: {right}\n" +
          $"Rects: {rects}\n" +
          $"Function: {MathFunctions.FunctionToString(func)}\n" +
          $"Integral: {integral}\n" +
          $"Time: {sw.Elapsed}\n\n");
      }
    }
  }
}
