using AgemarkerCore.Data;
using System;
using System.ComponentModel;
using System.Linq;
using System.Threading;

namespace AgemarkerCore
{
    public class Calculations
    {
        public event EventHandler<Events.CalculationsCompletedEventArgs> CalculationsCompletedEvent;
        private ManualResetEvent busyEvent = new ManualResetEvent(false);
        private BackgroundWorker worker = new BackgroundWorker();
        private RandomInt64 random;
        private double[] ElementsContent = new double[118];
        private double[] ElementsNewContent = new double[118];
        private double[] ElementsWeight = new double[118];
        private double[] OxidesContent = new double[53];
        private double[] OxidesOxygen = new double[53];
        private double[] OxidesPureElement = new double[53];
        private double[] OxidesWeightSum = new double[53];
        private double[] AtomNor = new double[118];
        private long[] AtomAll = new long[118];
        private long[] AtomAllEight = new long[118];
        private long AtomAllSum = new long();
        private long AtomAllEightSum = new long();
        private int AtomMultiplier = new int();
        private double[] OutputIab = new double[0];
        private int[] OutputIabCount = new int[0];
        private Logarithm LogBase = new Logarithm();

        public Calculations(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, int multiplier, Logarithm log)
        {
            LogBase = log;
            AtomMultiplier = multiplier;
            OxidesContent = oxidesContent;
            ElementsContent = elementsContent;
            ElementsWeight = elementsWeight;
            random = new RandomInt64(new Random((BitConverter.ToInt32(Guid.NewGuid().ToByteArray(), 4))));
            worker.DoWork += calculateIp;
            worker.RunWorkerCompleted += calculateResults;
        }

        public Calculations(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, int multiplier, Logarithm log, int randomSeed)
        {
            LogBase = log;
            AtomMultiplier = multiplier;
            OxidesContent = oxidesContent;
            ElementsContent = elementsContent;
            ElementsWeight = elementsWeight;
            random = new RandomInt64(new Random(randomSeed));
            worker.DoWork += calculateIp;
            worker.RunWorkerCompleted += calculateResults;
        }

        public void Start()
        {
            busyEvent.Set();
            if (!worker.IsBusy)
            {
                worker.RunWorkerAsync();
            }
        }

        public void Pause()
        {
            busyEvent.Reset();
        }

        private void calculateAtoms()
        {
            OxidesWeightSum[0] = ((ElementsWeight[13] * 1) + (ElementsWeight[7] * 2));
            OxidesWeightSum[1] = ((ElementsWeight[21] * 1) + (ElementsWeight[7] * 2));
            OxidesWeightSum[2] = ((ElementsWeight[12] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[3] = ((ElementsWeight[25] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[4] = ((ElementsWeight[25] * 1) + (ElementsWeight[7] * 1));
            OxidesWeightSum[5] = ((ElementsWeight[24] * 1) + (ElementsWeight[7] * 1));
            OxidesWeightSum[6] = ((ElementsWeight[11] * 1) + (ElementsWeight[7] * 1));
            OxidesWeightSum[7] = ((ElementsWeight[18] * 2) + (ElementsWeight[7] * 1));
            OxidesWeightSum[8] = ((ElementsWeight[19] * 1) + (ElementsWeight[7] * 1));
            OxidesWeightSum[9] = ((ElementsWeight[10] * 2) + (ElementsWeight[7] * 1));
            OxidesWeightSum[10] = ((ElementsWeight[0] * 2) + (ElementsWeight[7] * 1));
            OxidesWeightSum[11] = ((ElementsWeight[0] * 2) + (ElementsWeight[7] * 1));
            OxidesWeightSum[12] = ((ElementsWeight[14] * 2) + (ElementsWeight[7] * 5));
            OxidesWeightSum[13] = ((ElementsWeight[5] * 1) + (ElementsWeight[7] * 2));
            OxidesWeightSum[14] = ((ElementsWeight[4] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[15] = ((ElementsWeight[15] * 1) + (ElementsWeight[7] * 3));
            OxidesWeightSum[16] = ((ElementsWeight[22] * 2) + (ElementsWeight[7] * 5));
            OxidesWeightSum[17] = ((ElementsWeight[23] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[18] = ((ElementsWeight[27] * 1) + (ElementsWeight[7] * 1));
            OxidesWeightSum[19] = ((ElementsWeight[32] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[20] = ((ElementsWeight[38] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[21] = ((ElementsWeight[55] * 1) + (ElementsWeight[7] * 1));
            OxidesWeightSum[22] = ((ElementsWeight[56] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[23] = ((ElementsWeight[57] * 1) + (ElementsWeight[7] * 2));
            OxidesWeightSum[24] = ((ElementsWeight[58] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[25] = ((ElementsWeight[59] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[26] = ((ElementsWeight[61] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[27] = ((ElementsWeight[62] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[28] = ((ElementsWeight[63] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[29] = ((ElementsWeight[64] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[30] = ((ElementsWeight[65] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[31] = ((ElementsWeight[66] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[32] = ((ElementsWeight[67] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[33] = ((ElementsWeight[68] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[34] = ((ElementsWeight[69] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[35] = ((ElementsWeight[72] * 2) + (ElementsWeight[7] * 5));
            OxidesWeightSum[36] = ((ElementsWeight[73] * 1) + (ElementsWeight[7] * 3));
            OxidesWeightSum[37] = ((ElementsWeight[39] * 1) + (ElementsWeight[7] * 2));
            OxidesWeightSum[38] = ((ElementsWeight[2] * 2) + (ElementsWeight[7] * 1));
            OxidesWeightSum[39] = ((ElementsWeight[37] * 1) + (ElementsWeight[7] * 1));
            OxidesWeightSum[40] = ((ElementsWeight[81] * 1) + (ElementsWeight[7] * 1));
            OxidesWeightSum[41] = ((ElementsWeight[29] * 1) + (ElementsWeight[7] * 1));
            OxidesWeightSum[42] = ((ElementsWeight[89] * 1) + (ElementsWeight[7] * 2));
            OxidesWeightSum[43] = ((ElementsWeight[91] * 3) + (ElementsWeight[7] * 8));
            OxidesWeightSum[44] = ((ElementsWeight[24] * 3) + (ElementsWeight[7] * 4));
            OxidesWeightSum[45] = ((ElementsWeight[24] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[46] = ((ElementsWeight[50] * 2) + (ElementsWeight[7] * 3));
            OxidesWeightSum[47] = ((ElementsWeight[49] * 1) + (ElementsWeight[7] * 2));
            OxidesWeightSum[48] = ((ElementsWeight[71] * 1) + (ElementsWeight[7] * 2));
            OxidesWeightSum[49] = ((ElementsWeight[28] * 2) + (ElementsWeight[7] * 1));
            OxidesWeightSum[50] = ((ElementsWeight[43] * 1) + (ElementsWeight[7] * 2));
            OxidesWeightSum[51] = ((ElementsWeight[54] * 2) + (ElementsWeight[7] * 1));
            OxidesWeightSum[52] = ((ElementsWeight[36] * 2) + (ElementsWeight[7] * 1));
            OxidesPureElement[0] = ((ElementsWeight[13] * 1) * (OxidesContent[0]) / (OxidesWeightSum[0]));
            OxidesPureElement[1] = ((ElementsWeight[21] * 1) * (OxidesContent[1]) / (OxidesWeightSum[1]));
            OxidesPureElement[2] = ((ElementsWeight[12] * 2) * (OxidesContent[2]) / (OxidesWeightSum[2]));
            OxidesPureElement[3] = ((ElementsWeight[25] * 2) * (OxidesContent[3]) / (OxidesWeightSum[3]));
            OxidesPureElement[4] = ((ElementsWeight[25] * 1) * (OxidesContent[4]) / (OxidesWeightSum[4]));
            OxidesPureElement[5] = ((ElementsWeight[24] * 1) * (OxidesContent[5]) / (OxidesWeightSum[5]));
            OxidesPureElement[6] = ((ElementsWeight[11] * 1) * (OxidesContent[6]) / (OxidesWeightSum[6]));
            OxidesPureElement[7] = ((ElementsWeight[18] * 2) * (OxidesContent[7]) / (OxidesWeightSum[7]));
            OxidesPureElement[8] = ((ElementsWeight[19] * 1) * (OxidesContent[8]) / (OxidesWeightSum[8]));
            OxidesPureElement[9] = ((ElementsWeight[10] * 2) * (OxidesContent[9]) / (OxidesWeightSum[9]));
            OxidesPureElement[10] = ((ElementsWeight[0] * 2) * (OxidesContent[10]) / (OxidesWeightSum[10]));
            OxidesPureElement[11] = ((ElementsWeight[0] * 2) * (OxidesContent[11]) / (OxidesWeightSum[11]));
            OxidesPureElement[12] = ((ElementsWeight[14] * 2) * (OxidesContent[12]) / (OxidesWeightSum[12]));
            OxidesPureElement[13] = ((ElementsWeight[5] * 1) * (OxidesContent[13]) / (OxidesWeightSum[13]));
            OxidesPureElement[14] = ((ElementsWeight[4] * 2) * (OxidesContent[14]) / (OxidesWeightSum[14]));
            OxidesPureElement[15] = ((ElementsWeight[15] * 1) * (OxidesContent[15]) / (OxidesWeightSum[15]));
            OxidesPureElement[16] = ((ElementsWeight[22] * 2) * (OxidesContent[16]) / (OxidesWeightSum[16]));
            OxidesPureElement[17] = ((ElementsWeight[23] * 2) * (OxidesContent[17]) / (OxidesWeightSum[17]));
            OxidesPureElement[18] = ((ElementsWeight[27] * 1) * (OxidesContent[18]) / (OxidesWeightSum[18]));
            OxidesPureElement[19] = ((ElementsWeight[32] * 2) * (OxidesContent[19]) / (OxidesWeightSum[19]));
            OxidesPureElement[20] = ((ElementsWeight[38] * 2) * (OxidesContent[20]) / (OxidesWeightSum[20]));
            OxidesPureElement[21] = ((ElementsWeight[55] * 1) * (OxidesContent[21]) / (OxidesWeightSum[21]));
            OxidesPureElement[22] = ((ElementsWeight[56] * 2) * (OxidesContent[22]) / (OxidesWeightSum[22]));
            OxidesPureElement[23] = ((ElementsWeight[57] * 1) * (OxidesContent[23]) / (OxidesWeightSum[23]));
            OxidesPureElement[24] = ((ElementsWeight[58] * 2) * (OxidesContent[24]) / (OxidesWeightSum[24]));
            OxidesPureElement[25] = ((ElementsWeight[59] * 2) * (OxidesContent[25]) / (OxidesWeightSum[25]));
            OxidesPureElement[26] = ((ElementsWeight[61] * 2) * (OxidesContent[26]) / (OxidesWeightSum[26]));
            OxidesPureElement[27] = ((ElementsWeight[62] * 2) * (OxidesContent[27]) / (OxidesWeightSum[27]));
            OxidesPureElement[28] = ((ElementsWeight[63] * 2) * (OxidesContent[28]) / (OxidesWeightSum[28]));
            OxidesPureElement[29] = ((ElementsWeight[64] * 2) * (OxidesContent[29]) / (OxidesWeightSum[29]));
            OxidesPureElement[30] = ((ElementsWeight[65] * 2) * (OxidesContent[30]) / (OxidesWeightSum[30]));
            OxidesPureElement[31] = ((ElementsWeight[66] * 2) * (OxidesContent[31]) / (OxidesWeightSum[31]));
            OxidesPureElement[32] = ((ElementsWeight[67] * 2) * (OxidesContent[32]) / (OxidesWeightSum[32]));
            OxidesPureElement[33] = ((ElementsWeight[68] * 2) * (OxidesContent[33]) / (OxidesWeightSum[33]));
            OxidesPureElement[34] = ((ElementsWeight[69] * 2) * (OxidesContent[34]) / (OxidesWeightSum[34]));
            OxidesPureElement[35] = ((ElementsWeight[72] * 2) * (OxidesContent[35]) / (OxidesWeightSum[35]));
            OxidesPureElement[36] = ((ElementsWeight[73] * 1) * (OxidesContent[36]) / (OxidesWeightSum[36]));
            OxidesPureElement[37] = ((ElementsWeight[39] * 1) * (OxidesContent[37]) / (OxidesWeightSum[37]));
            OxidesPureElement[38] = ((ElementsWeight[2] * 2) * (OxidesContent[38]) / (OxidesWeightSum[38]));
            OxidesPureElement[39] = ((ElementsWeight[37] * 1) * (OxidesContent[39]) / (OxidesWeightSum[39]));
            OxidesPureElement[40] = ((ElementsWeight[81] * 1) * (OxidesContent[40]) / (OxidesWeightSum[40]));
            OxidesPureElement[41] = ((ElementsWeight[29] * 1) * (OxidesContent[41]) / (OxidesWeightSum[41]));
            OxidesPureElement[42] = ((ElementsWeight[89] * 1) * (OxidesContent[42]) / (OxidesWeightSum[42]));
            OxidesPureElement[43] = ((ElementsWeight[91] * 3) * (OxidesContent[43]) / (OxidesWeightSum[43]));
            OxidesPureElement[44] = ((ElementsWeight[24] * 3) * (OxidesContent[44]) / (OxidesWeightSum[44]));
            OxidesPureElement[45] = ((ElementsWeight[24] * 2) * (OxidesContent[45]) / (OxidesWeightSum[45]));
            OxidesPureElement[46] = ((ElementsWeight[50] * 2) * (OxidesContent[46]) / (OxidesWeightSum[46]));
            OxidesPureElement[47] = ((ElementsWeight[49] * 1) * (OxidesContent[47]) / (OxidesWeightSum[47]));
            OxidesPureElement[48] = ((ElementsWeight[71] * 1) * (OxidesContent[48]) / (OxidesWeightSum[48]));
            OxidesPureElement[49] = ((ElementsWeight[28] * 2) * (OxidesContent[49]) / (OxidesWeightSum[49]));
            OxidesPureElement[50] = ((ElementsWeight[43] * 1) * (OxidesContent[50]) / (OxidesWeightSum[50]));
            OxidesPureElement[51] = ((ElementsWeight[54] * 2) * (OxidesContent[51]) / (OxidesWeightSum[51]));
            OxidesPureElement[52] = ((ElementsWeight[36] * 2) * (OxidesContent[52]) / (OxidesWeightSum[52]));
            for (int x = 0; x < 53; x++)
            {
                OxidesOxygen[x] = ((OxidesContent[x]) - (OxidesPureElement[x]));
            }
            for (int x = 0; x < 118; x++)
            {
                ElementsNewContent[x] = ElementsContent[x];
            }
            ElementsNewContent[13] += OxidesPureElement[0];
            ElementsNewContent[21] += OxidesPureElement[1];
            ElementsNewContent[12] += OxidesPureElement[2];
            ElementsNewContent[25] += OxidesPureElement[3];
            ElementsNewContent[25] += OxidesPureElement[4];
            ElementsNewContent[24] += OxidesPureElement[5];
            ElementsNewContent[11] += OxidesPureElement[6];
            ElementsNewContent[18] += OxidesPureElement[7];
            ElementsNewContent[19] += OxidesPureElement[8];
            ElementsNewContent[10] += OxidesPureElement[9];
            ElementsNewContent[0] += OxidesPureElement[10];
            ElementsNewContent[0] += OxidesPureElement[11];
            ElementsNewContent[14] += OxidesPureElement[12];
            ElementsNewContent[5] += OxidesPureElement[13];
            ElementsNewContent[4] += OxidesPureElement[14];
            ElementsNewContent[15] += OxidesPureElement[15];
            ElementsNewContent[22] += OxidesPureElement[16];
            ElementsNewContent[23] += OxidesPureElement[17];
            ElementsNewContent[27] += OxidesPureElement[18];
            ElementsNewContent[32] += OxidesPureElement[19];
            ElementsNewContent[38] += OxidesPureElement[20];
            ElementsNewContent[55] += OxidesPureElement[21];
            ElementsNewContent[56] += OxidesPureElement[22];
            ElementsNewContent[57] += OxidesPureElement[23];
            ElementsNewContent[58] += OxidesPureElement[24];
            ElementsNewContent[59] += OxidesPureElement[25];
            ElementsNewContent[61] += OxidesPureElement[26];
            ElementsNewContent[62] += OxidesPureElement[27];
            ElementsNewContent[63] += OxidesPureElement[28];
            ElementsNewContent[64] += OxidesPureElement[29];
            ElementsNewContent[65] += OxidesPureElement[30];
            ElementsNewContent[66] += OxidesPureElement[31];
            ElementsNewContent[67] += OxidesPureElement[32];
            ElementsNewContent[68] += OxidesPureElement[33];
            ElementsNewContent[69] += OxidesPureElement[34];
            ElementsNewContent[72] += OxidesPureElement[35];
            ElementsNewContent[73] += OxidesPureElement[36];
            ElementsNewContent[39] += OxidesPureElement[37];
            ElementsNewContent[2] += OxidesPureElement[38];
            ElementsNewContent[37] += OxidesPureElement[39];
            ElementsNewContent[81] += OxidesPureElement[40];
            ElementsNewContent[29] += OxidesPureElement[41];
            ElementsNewContent[89] += OxidesPureElement[42];
            ElementsNewContent[91] += OxidesPureElement[43];
            ElementsNewContent[24] += OxidesPureElement[44];
            ElementsNewContent[24] += OxidesPureElement[45];
            ElementsNewContent[50] += OxidesPureElement[46];
            ElementsNewContent[49] += OxidesPureElement[47];
            ElementsNewContent[71] += OxidesPureElement[48];
            ElementsNewContent[28] += OxidesPureElement[49];
            ElementsNewContent[43] += OxidesPureElement[50];
            ElementsNewContent[54] += OxidesPureElement[51];
            ElementsNewContent[36] += OxidesPureElement[52];
            for (int x = 0; x < 53; x++)
            {
                ElementsNewContent[7] += OxidesOxygen[x];
            }
            for (int x = 0; x < 118; x++)
            {
                AtomNor[x] = (ElementsNewContent[x] / ElementsWeight[x]);
            }
            for (int x = 0; x < 118; x++)
            {
                string s = Math.Round((AtomNor[x] * AtomMultiplier), 0).ToString();
                try
                {
                    AtomAll[x] = int.Parse(s);
                }
                catch
                {
                }
            }
            for (int x = 0; x < 118; x++)
            {
                AtomAllSum += AtomAll[x];
            }
            for (int x = 0; x < 118; x++)
            {
                AtomAllEight[x] = (AtomAll[x] * 8);
            }
            for (int x = 0; x < 118; x++)
            {
                AtomAllEightSum += AtomAllEight[x];
            }
        }

        private void calculateIp(object sender, DoWorkEventArgs e)
        {
            calculateAtoms();
            double[] input = new double[9];
            long[] count = new long[118];
            double iab;
            long r, rr;
            for (long x = 0; x < AtomAllSum; x++)
            {
                busyEvent.WaitOne();
                iab = 0;
                for (int ww = 0; ww < 9; ww++)
                {
                    input[ww] = 0;
                }
                for (int y = 0; y < 8; y++)
                {
                    if (input[y] == 0)
                    {
                        do
                        {
                            r = random.Next(1, (AtomAllEightSum));
                            rr = 0;
                            for (int z = 0; z < 118; z++)
                            {
                                if (AtomAllEight[z] != 0)
                                {
                                    rr += AtomAllEight[z];
                                    if (r <= rr && count[z] < AtomAllEight[z])
                                    {
                                        input[y] = ElementsWeight[z];
                                        count[z]++;
                                        break;
                                    }
                                }
                            }
                        } while (input[y] == 0);
                    }
                }
                for (int w = 0; w < 8; w++)
                {
                    input[8] += input[w];
                }
                if (LogBase == Logarithm.Natural)
                {
                    iab = Mathematics.Iab(input);
                }
                else
                {
                    iab = Mathematics.Iab10(input);
                }
                iab = Math.Round(iab, 10);
                bool inputNew = true;
                int outputIabLength = OutputIab.Length;
                for (int v = 0; v < outputIabLength; v++)
                {
                    if (OutputIab[v] == iab)
                    {
                        inputNew = false;
                        OutputIabCount[v]++;
                        break;
                    }
                }
                if (inputNew == true)
                {
                    Array.Resize(ref OutputIab, (OutputIab.Length + 1));
                    Array.Resize(ref OutputIabCount, (OutputIabCount.Length + 1));
                    OutputIab[(OutputIab.Length - 1)] = iab;
                    OutputIabCount[(OutputIabCount.Length - 1)]++;
                }
            }
        }

        private void calculateResults(object sender, RunWorkerCompletedEventArgs e)
        {
            int iabCount = OutputIab.Count();
            double[] OutputIabSqrt = new double[iabCount];
            double outputIabSum = 0;
            double outputIabSqrtSum = 0;
            double outputIabAvg = 0;
            double outputIabSqrtAvg = 0;
            double outputVariance = 0;
            double outputVarianceSqrt = 0;
            double outputVarianceIab = 0;
            double outputVarianceIabSqrt = 0;
            double outputIabRange = 0;
            double outputIabIntervalLength = 0;
            double outputIabRangeSqrt = 0;
            double outputIabIntervalLengthSqrt = 0;
            double[,] outputIabIntervals = new double[7, 2];
            double[] outputIabIntervalsCenters = new double[7];
            double[,] outputIabIntervalsSqrt = new double[7, 2];
            double[] outputIabIntervalsCentersSqrt = new double[7];
            long[] outputIabIntervalsCount = new long[7];
            long[] outputIabIntervalsCountSqrt = new long[7];
            Array.Sort(OutputIab, OutputIabCount);
            for (int x = 0; x < iabCount; x++)
            {
                OutputIabSqrt[x] = Math.Sqrt(OutputIab[x]);
            }
            try
            {
                for (int x = 0; x < iabCount; x++)
                {
                    outputIabSum += ((OutputIab[x] * OutputIabCount[x]));
                    outputIabSqrtSum += (OutputIabSqrt[x] * OutputIabCount[x]);
                    outputVariance += (Math.Pow((OutputIabSqrt[x] - outputIabSqrtAvg), 2) * OutputIabCount[x]);
                    outputVarianceIab += (Math.Pow((OutputIab[x] - outputIabAvg), 2) * OutputIabCount[x]);
                }
                outputIabAvg = (outputIabSum / AtomAllSum);
                outputIabSqrtAvg = (outputIabSqrtSum / AtomAllSum);
                outputVariance = (outputVariance / (AtomAllSum - 1));
                outputVarianceIab = (outputVarianceIab / (AtomAllSum - 1));
                outputVarianceSqrt = Math.Sqrt(outputVariance);
                outputVarianceIabSqrt = Math.Sqrt(outputVarianceIab);
                outputIabRange = (OutputIab[(iabCount - 1)] - OutputIab[0]);
                outputIabIntervalLength = (outputIabRange / 7);
                outputIabRangeSqrt = (Math.Sqrt(OutputIab[(iabCount - 1)]) - Math.Sqrt(OutputIab[0]));
                outputIabIntervalLengthSqrt = (outputIabRangeSqrt / 7);
                for (int x = 0; x < 7; x++)
                {
                    outputIabIntervals[x, 0] = (OutputIab[0] + (outputIabIntervalLength * x));
                    outputIabIntervals[x, 1] = (OutputIab[0] + (outputIabIntervalLength * (x + 1)));
                    outputIabIntervalsCenters[x] = ((outputIabIntervals[x, 0] + outputIabIntervals[x, 1]) / 2);
                    outputIabIntervalsSqrt[x, 0] = (Math.Sqrt(OutputIab[0]) + (outputIabIntervalLengthSqrt * x));
                    outputIabIntervalsSqrt[x, 1] = (Math.Sqrt(OutputIab[0]) + (outputIabIntervalLengthSqrt * (x + 1)));
                    outputIabIntervalsCentersSqrt[x] = ((outputIabIntervalsSqrt[x, 0] + outputIabIntervalsSqrt[x, 1]) / 2);
                }
                for (int x = 0; x < iabCount; x++)
                {
                    for (int y = 0; y < 7; y++)
                    {
                        if (OutputIab[x] <= outputIabIntervals[y, 1])
                        {
                            outputIabIntervalsCount[y] += OutputIabCount[x];
                            break;
                        }
                    }
                    for (int y = 0; y < 7; y++)
                    {
                        if (OutputIabSqrt[x] <= outputIabIntervalsSqrt[y, 1])
                        {
                            outputIabIntervalsCountSqrt[y] += OutputIabCount[x];
                            break;
                        }
                    }
                }
            }
            catch
            {
            }
            Results r = new Results();
            r.OxidesContent = OxidesContent;
            r.ElementsWeight = ElementsWeight;
            r.ElementsContent = ElementsContent;
            r.Multiplier = AtomMultiplier;
            r.Logarithm = LogBase;
            r.Atoms = AtomAllEight;
            r.AtomsSum = AtomAllEightSum;
            r.Ip = OutputIab;
            r.IpSqrt = OutputIabSqrt;
            r.IpCount = OutputIabCount;
            r.IpAverage = outputIabAvg;
            r.IpVariance = outputVarianceIab;
            r.IpStandartDeviation = outputVarianceIabSqrt;
            r.IpSqrtAverage = outputIabSqrtAvg;
            r.IpSqrtVariance = outputVariance;
            r.IpSqrtStandartDeviation = outputVarianceSqrt;
            r.IpRange = outputIabRange;
            r.IpSqrtRange = outputIabRangeSqrt;
            r.IpIntervalLength = outputIabIntervalLength;
            r.IpSqrtIntervalLength = outputIabIntervalLengthSqrt;
            r.IpIntervalMinimum = new double[7];
            r.IpIntervalMaximum = new double[7];
            r.IpSqrtIntervalMinimum = new double[7];
            r.IpSqrtIntervalMaximum = new double[7];
            for (int x = 0; x < 7; x++)
            {
                r.IpIntervalMinimum[x] = outputIabIntervals[x, 0];
                r.IpIntervalMaximum[x] = outputIabIntervals[x, 1];
                r.IpSqrtIntervalMinimum[x] = outputIabIntervalsSqrt[x, 0];
                r.IpSqrtIntervalMaximum[x] = outputIabIntervalsSqrt[x, 1];
            }
            r.IpIntervalCenter = outputIabIntervalsCenters;
            r.IpIntervalCount = outputIabIntervalsCount;
            r.IpSqrtIntervalCenter = outputIabIntervalsCentersSqrt;
            r.IpSqrtIntervalCount = outputIabIntervalsCountSqrt;
            raiseCalculationsCompletedEvent(r);
        }

        protected virtual void raiseCalculationsCompletedEvent(Results results)
        {
            if (CalculationsCompletedEvent != null)
            {
                CalculationsCompletedEvent(this, new Events.CalculationsCompletedEventArgs(results));
            }
        }
    }
}
