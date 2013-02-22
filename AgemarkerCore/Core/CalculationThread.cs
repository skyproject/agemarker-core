using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Threading;

namespace AgemarkerCore.Core
{
    public partial class CalculationsThread
    {
        public event EventHandler<Events.ThreadCalculationsCompletedEventArgs> ThreadCalculationsCompletedEvent;
        double[] elementsWeight = new double[118];
        long[] atomAllEight = new long[118];
        long atomAllEightSum;
        Data.Logarithm logarithm;
        BackgroundWorker worker = new BackgroundWorker();
        SortedDictionary<double, int> OutputIab = new SortedDictionary<double, int>();
        ManualResetEvent busyEvent = new ManualResetEvent(false);
        RandomInt64 random;
        long startIteration;
        long endIteration;

        public CalculationsThread(double[] elementsWeight, long[] atomAllEight, long atomAllEightSum, Data.Logarithm logarithm, long startIteration, long endIteration)
        {
            this.elementsWeight = elementsWeight;
            this.atomAllEight = atomAllEight;
            this.atomAllEightSum = atomAllEightSum;
            this.logarithm = logarithm;
            this.random = new RandomInt64(new Random((BitConverter.ToInt32(Guid.NewGuid().ToByteArray(), 4))));
            this.startIteration = startIteration;
            this.endIteration = endIteration;
            worker.DoWork += CalculateIp;
            worker.RunWorkerCompleted += CalculationsCompleted;
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

        private void CalculateIp(object sender, DoWorkEventArgs e)
        {
            double[] input = new double[9];
            long[] count = new long[118];
            double iab;
            long r, rr;
            for (long x = startIteration; x < endIteration; x++)
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
                            r = random.Next(1, (atomAllEightSum));
                            rr = 0;
                            for (int z = 0; z < 118; z++)
                            {
                                if (atomAllEight[z] != 0)
                                {
                                    rr += atomAllEight[z];
                                    if (r <= rr && count[z] < atomAllEight[z])
                                    {
                                        input[y] = elementsWeight[z];
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
                if (logarithm == Data.Logarithm.Natural)
                {
                    iab = Mathematics.Iab(input);
                }
                else
                {
                    iab = Mathematics.Iab10(input);
                }
                iab = Math.Round(iab, 10);
                if (OutputIab.ContainsKey(iab))
                {
                    OutputIab[iab]++;
                }
                else
                {
                    OutputIab[iab] = 1;
                }
            }
        }

        private void CalculationsCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (ThreadCalculationsCompletedEvent != null)
            {
                ThreadCalculationsCompletedEvent(this, new Events.ThreadCalculationsCompletedEventArgs(OutputIab));
            }
        }
    }
}