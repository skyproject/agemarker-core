using AgemarkerCore.Data;
using System;
using System.ComponentModel;
using System.Linq;
using System.Threading;
using System.Collections.Generic;

namespace AgemarkerCore
{
    public class Calculations
    {
        public event EventHandler<Events.CalculationsCompletedEventArgs> CalculationsCompletedEvent;
        SortedDictionary<double, int> OutputIab = new SortedDictionary<double, int>();
        double[] ElementsContent = new double[118];
        double[] ElementsNewContent = new double[118];
        double[] ElementsWeight = new double[118];
        double[] OxidesContent = new double[53];
        double[] OxidesOxygen = new double[53];
        double[] OxidesPureElement = new double[53];
        double[] OxidesWeightSum = new double[53];
        double[] AtomNor = new double[118];
        long[] AtomAll = new long[118];
        long[] AtomAllEight = new long[118];
        long AtomAllSum = new long();
        long AtomAllEightSum = new long();
        long AtomMultiplier = new long();
        int IntervalsNumber = new int();
        Logarithm LogBase = new Logarithm();
        Core.CalculationsThread[] workers;
        int runningThreads = 1;

        public Calculations(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, long multiplier, int intervalsNumber, Logarithm log)
        {
            LogBase = log;
            AtomMultiplier = multiplier;
            OxidesContent = oxidesContent;
            ElementsContent = elementsContent;
            ElementsWeight = elementsWeight;
            IntervalsNumber = intervalsNumber;
            workers = new Core.CalculationsThread[1];
            CalculateAtoms();
            workers[0] = new Core.CalculationsThread(ElementsWeight, AtomAllEight, AtomAllEightSum, LogBase, 0, AtomAllSum);
            workers[0].ThreadCalculationsCompletedEvent += ThreadFinished;
        }

        public Calculations(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, long multiplier, int intervalsNumber, Logarithm log, int coresNumber)
        {
            LogBase = log;
            AtomMultiplier = multiplier;
            OxidesContent = oxidesContent;
            ElementsContent = elementsContent;
            ElementsWeight = elementsWeight;
            IntervalsNumber = intervalsNumber;
            runningThreads = coresNumber;
            workers = new Core.CalculationsThread[coresNumber];
            CalculateAtoms();
            double lenth = AtomAllSum / coresNumber;
            long threadIterationsLength = long.Parse((Math.Round(lenth)).ToString());
            for (int x = 0; x < coresNumber; x++)
            {
                long start = threadIterationsLength * x;
                long end = 0;
                if ((x + 1) == coresNumber)
                {
                    end = AtomAllSum;
                }
                else
                {
                    end = threadIterationsLength * (x + 1);
                }
                workers[x] = new Core.CalculationsThread(ElementsWeight, AtomAllEight, AtomAllEightSum, LogBase, start, end);
                workers[x].ThreadCalculationsCompletedEvent += ThreadFinished;
            }
        }

        public void Start()
        {
            foreach (Core.CalculationsThread worker in workers)
            {
                worker.Start();
            }
        }

        public void Pause()
        {            
            foreach (Core.CalculationsThread worker in workers)
            {
                worker.Pause();
            }
        }

        private void CalculateAtoms()
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
                long.TryParse(s, out AtomAll[x]);
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

        private void ThreadFinished(object sender, Events.ThreadCalculationsCompletedEventArgs e)
        {
            foreach (KeyValuePair<double, int> kvp in e.Ip)
            {
                if (OutputIab.ContainsKey(kvp.Key))
                {
                    OutputIab[kvp.Key] += kvp.Value;
                }
                else
                {
                    OutputIab[kvp.Key] = kvp.Value;
                }
            }
            runningThreads--;
            if (runningThreads == 0)
            {
                CalculateResults();
            }
        }

        private void CalculateResults()
        {
            int iabCount = OutputIab.Count();
            double[] Iab = new double[iabCount];
            double[] IabSqrt = new double[iabCount];
            int[] IabCount = new int[iabCount];
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
            double[,] outputIabIntervals = new double[IntervalsNumber, 2];
            double[] outputIabIntervalsCenters = new double[IntervalsNumber];
            double[,] outputIabIntervalsSqrt = new double[IntervalsNumber, 2];
            double[] outputIabIntervalsCentersSqrt = new double[IntervalsNumber];
            long[] outputIabIntervalsCount = new long[IntervalsNumber];
            long[] outputIabIntervalsCountSqrt = new long[IntervalsNumber];
            int i = 0;
            foreach (KeyValuePair<double, int> kvp in OutputIab)
            {
                Iab[i] = kvp.Key;
                IabSqrt[i] = Math.Sqrt(kvp.Key);
                IabCount[i] = kvp.Value;                
                i++;
            }
            OutputIab.Clear();
            try
            {
                for (int x = 0; x < iabCount; x++)
                {
                    outputIabSum += ((Iab[x] * IabCount[x]));
                    outputIabSqrtSum += (IabSqrt[x] * IabCount[x]);
                }
                outputIabAvg = (outputIabSum / AtomAllSum);
                outputIabSqrtAvg = (outputIabSqrtSum / AtomAllSum);
                for (int x = 0; x < iabCount; x++)
                {
                    outputVariance += (Math.Pow((IabSqrt[x] - outputIabSqrtAvg), 2) * IabCount[x]);
                    outputVarianceIab += (Math.Pow((Iab[x] - outputIabAvg), 2) * IabCount[x]);
                }
                outputVariance = (outputVariance / (AtomAllSum - 1));
                outputVarianceIab = (outputVarianceIab / (AtomAllSum - 1));
                outputVarianceSqrt = Math.Sqrt(outputVariance);
                outputVarianceIabSqrt = Math.Sqrt(outputVarianceIab);
                outputIabRange = (Iab[(iabCount - 1)] - Iab[0]);
                outputIabIntervalLength = (outputIabRange / IntervalsNumber);
                outputIabRangeSqrt = (Math.Sqrt(Iab[(iabCount - 1)]) - Math.Sqrt(Iab[0]));
                outputIabIntervalLengthSqrt = (outputIabRangeSqrt / IntervalsNumber);
                for (int x = 0; x < IntervalsNumber; x++)
                {
                    outputIabIntervals[x, 0] = (Iab[0] + (outputIabIntervalLength * x));
                    outputIabIntervals[x, 1] = (Iab[0] + (outputIabIntervalLength * (x + 1)));
                    outputIabIntervalsCenters[x] = ((outputIabIntervals[x, 0] + outputIabIntervals[x, 1]) / 2);
                    outputIabIntervalsSqrt[x, 0] = (Math.Sqrt(Iab[0]) + (outputIabIntervalLengthSqrt * x));
                    outputIabIntervalsSqrt[x, 1] = (Math.Sqrt(Iab[0]) + (outputIabIntervalLengthSqrt * (x + 1)));
                    outputIabIntervalsCentersSqrt[x] = ((outputIabIntervalsSqrt[x, 0] + outputIabIntervalsSqrt[x, 1]) / 2);
                }
                for (int x = 0; x < iabCount; x++)
                {
                    for (int y = 0; y < IntervalsNumber; y++)
                    {
                        if (Iab[x] <= outputIabIntervals[y, 1])
                        {
                            outputIabIntervalsCount[y] += IabCount[x];
                            break;
                        }
                    }
                    for (int y = 0; y < IntervalsNumber; y++)
                    {
                        if (IabSqrt[x] <= outputIabIntervalsSqrt[y, 1])
                        {
                            outputIabIntervalsCountSqrt[y] += IabCount[x];
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
            r.IntervalsNumber = IntervalsNumber;
            r.Logarithm = LogBase;
            r.Atoms = AtomAllEight;
            r.AtomsSum = AtomAllEightSum;
            r.Ip = Iab;
            r.IpSqrt = IabSqrt;
            r.IpCount = IabCount;
            r.IpAverage = outputIabAvg;
            r.IpVariance = outputVarianceIab;
            r.IpStandardDeviation = outputVarianceIabSqrt;
            r.IpSqrtAverage = outputIabSqrtAvg;
            r.IpSqrtVariance = outputVariance;
            r.IpSqrtStandardDeviation = outputVarianceSqrt;
            r.IpRange = outputIabRange;
            r.IpSqrtRange = outputIabRangeSqrt;
            r.IpIntervalLength = outputIabIntervalLength;
            r.IpSqrtIntervalLength = outputIabIntervalLengthSqrt;
            r.IpIntervalMinimum = new double[IntervalsNumber];
            r.IpIntervalMaximum = new double[IntervalsNumber];
            r.IpSqrtIntervalMinimum = new double[IntervalsNumber];
            r.IpSqrtIntervalMaximum = new double[IntervalsNumber];
            for (int x = 0; x < IntervalsNumber; x++)
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
            if (CalculationsCompletedEvent != null)
            {
                CalculationsCompletedEvent(this, new Events.CalculationsCompletedEventArgs(r));
            }
        }
    }
}