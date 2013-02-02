using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AgemarkerCore
{
    public partial class RandomInt64
    {
        Random random;

        public RandomInt64(Random rnd)
        {
            random = rnd;
        }

        public Int64 Next(long minValue, long maxValue)
        {
            byte[] randomBytes = new byte[8];
            random.NextBytes(randomBytes);
            long value = BitConverter.ToInt64(randomBytes, 0);
            return (Math.Abs(value % (maxValue - minValue)) + minValue);
        }
    }
}
