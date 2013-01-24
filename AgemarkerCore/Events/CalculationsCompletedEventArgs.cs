using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AgemarkerCore.Events
{
    public class CalculationsCompletedEventArgs : EventArgs
    {
        public Data.Results Results { get; set; }

        public CalculationsCompletedEventArgs(Data.Results results)
        {
            this.Results = results;
        }
    }
}
