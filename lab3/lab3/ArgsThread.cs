using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    public class ArgsThread
    {
        public long left;

        public long right;

        public double step;

        public ArgsThread(long left, long right, double step)
        {
            this.left = left;
            this.right = right;
            this.step = step;
        }
    }
}
