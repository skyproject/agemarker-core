using System;

namespace AgemarkerCore
{
    public class Mathematics
    {
        public static double Iab(double[] input)
        {
            double f14 = 0, f15 = 0, f16 = 0, f17 = 0;
            double c20 = 0, c21 = 0, c22 = 0;
            double ka = 0, kb = 0, kab = 0, iab = 0;
            f14 = input[0] + input[1] + input[2];
            f15 = input[3] + input[4] + input[5];
            f16 = input[6] + input[7] + input[8];
            f17 = f14 + f15 + f16;
            c20 = input[0] + input[3] + input[6];
            c21 = input[1] + input[4] + input[7];
            c22 = input[2] + input[5] + input[8];
            if (f14 > 0)
                f14 = Math.Abs(f14 / f17 * Math.Log(f14 / f17));
            if (f15 > 0)
                f15 = Math.Abs(f15 / f17 * Math.Log(f15 / f17));
            if (f16 > 0)
                f16 = Math.Abs(f16 / f17 * Math.Log(f16 / f17));
            if (c20 > 0)
                c20 = Math.Abs(c20 / f17 * Math.Log(c20 / f17));
            if (c21 > 0)
                c21 = Math.Abs(c21 / f17 * Math.Log(c21 / f17));
            if (c22 > 0)
                c22 = Math.Abs(c22 / f17 * Math.Log(c22 / f17));
            ka = f14 + f15 + f16;
            kb = c20 + c21 + c22;
            kab = 0;
            if (input[0] > 0)
                kab = kab + Math.Abs(input[0] / f17 * Math.Log(input[0] / f17));
            if (input[1] > 0)
                kab = kab + Math.Abs(input[1] / f17 * Math.Log(input[1] / f17));
            if (input[2] > 0)
                kab = kab + Math.Abs(input[2] / f17 * Math.Log(input[2] / f17));
            if (input[3] > 0)
                kab = kab + Math.Abs(input[3] / f17 * Math.Log(input[3] / f17));
            if (input[4] > 0)
                kab = kab + Math.Abs(input[4] / f17 * Math.Log(input[4] / f17));
            if (input[5] > 0)
                kab = kab + Math.Abs(input[5] / f17 * Math.Log(input[5] / f17));
            if (input[6] > 0)
                kab = kab + Math.Abs(input[6] / f17 * Math.Log(input[6] / f17));
            if (input[7] > 0)
                kab = kab + Math.Abs(input[7] / f17 * Math.Log(input[7] / f17));
            if (input[8] > 0)
                kab = kab + Math.Abs(input[8] / f17 * Math.Log(input[8] / f17));
            iab = (ka + kb - kab);
            return iab;
        }

        public static double Iab10(double[] input)
        {
            double f14 = 0, f15 = 0, f16 = 0, f17 = 0;
            double c20 = 0, c21 = 0, c22 = 0;
            double ka = 0, kb = 0, kab = 0, iab = 0;
            f14 = input[0] + input[1] + input[2];
            f15 = input[3] + input[4] + input[5];
            f16 = input[6] + input[7] + input[8];
            f17 = f14 + f15 + f16;
            c20 = input[0] + input[3] + input[6];
            c21 = input[1] + input[4] + input[7];
            c22 = input[2] + input[5] + input[8];
            if (f14 > 0)
                f14 = Math.Abs(f14 / f17 * Math.Log10(f14 / f17));
            if (f15 > 0)
                f15 = Math.Abs(f15 / f17 * Math.Log10(f15 / f17));
            if (f16 > 0)
                f16 = Math.Abs(f16 / f17 * Math.Log10(f16 / f17));
            if (c20 > 0)
                c20 = Math.Abs(c20 / f17 * Math.Log10(c20 / f17));
            if (c21 > 0)
                c21 = Math.Abs(c21 / f17 * Math.Log10(c21 / f17));
            if (c22 > 0)
                c22 = Math.Abs(c22 / f17 * Math.Log10(c22 / f17));
            ka = f14 + f15 + f16;
            kb = c20 + c21 + c22;
            kab = 0;
            if (input[0] > 0)
                kab = kab + Math.Abs(input[0] / f17 * Math.Log10(input[0] / f17));
            if (input[1] > 0)
                kab = kab + Math.Abs(input[1] / f17 * Math.Log10(input[1] / f17));
            if (input[2] > 0)
                kab = kab + Math.Abs(input[2] / f17 * Math.Log10(input[2] / f17));
            if (input[3] > 0)
                kab = kab + Math.Abs(input[3] / f17 * Math.Log10(input[3] / f17));
            if (input[4] > 0)
                kab = kab + Math.Abs(input[4] / f17 * Math.Log10(input[4] / f17));
            if (input[5] > 0)
                kab = kab + Math.Abs(input[5] / f17 * Math.Log10(input[5] / f17));
            if (input[6] > 0)
                kab = kab + Math.Abs(input[6] / f17 * Math.Log10(input[6] / f17));
            if (input[7] > 0)
                kab = kab + Math.Abs(input[7] / f17 * Math.Log10(input[7] / f17));
            if (input[8] > 0)
                kab = kab + Math.Abs(input[8] / f17 * Math.Log10(input[8] / f17));
            iab = (ka + kb - kab);
            return iab;
        }
    }
}
