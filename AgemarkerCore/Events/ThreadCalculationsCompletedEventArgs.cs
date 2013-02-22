using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AgemarkerCore.Events
{
    public partial class ThreadCalculationsCompletedEventArgs : EventArgs
    {
        public SortedDictionary<double, int> Ip { get; set; }

        public ThreadCalculationsCompletedEventArgs(SortedDictionary<double, int> ip)
        {
            this.Ip = ip;
        }
    }
}