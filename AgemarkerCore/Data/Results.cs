using System;

namespace AgemarkerCore.Data
{
    public struct Results
    {
        public AgemarkerCore.Data.Logarithm Logarithm { get; set; }
        public double[] ElementsContent { get; set; }
        public double[] ElementsWeight { get; set; }
        public double[] OxidesContent { get; set; }    
        public long[] Atoms { get; set; }
        public long AtomsSum { get; set; }
        public int Multiplier { get; set; }
        public double[] Ip { get; set; }
        public double[] IpSqrt { get; set; }
        public int[] IpCount { get; set; }
        public double IpAverage { get; set; }
        public double IpSqrtAverage { get; set; }
        public double IpVariance { get; set; }
        public double IpSqrtVariance { get; set; }
        public double IpStandartDeviation { get; set; }
        public double IpSqrtStandartDeviation { get; set; }
        public double IpRange { get; set; }
        public double IpSqrtRange { get; set; }
        public double IpIntervalLength { get; set; }
        public double IpSqrtIntervalLength { get; set; }
        public double[] IpIntervalMinimum { get; set; }
        public double[] IpSqrtIntervalMinimum { get; set; }
        public double[] IpIntervalMaximum { get; set; }
        public double[] IpSqrtIntervalMaximum { get; set; }
        public double[] IpIntervalCenter { get; set; }
        public double[] IpSqrtIntervalCenter { get; set; }
        public long[] IpIntervalCount { get; set; }
        public long[] IpSqrtIntervalCount { get; set; }
    }
}
