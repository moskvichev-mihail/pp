using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    public class ICriticalSectionImplementation : ICriticalSection
    {
        public void Enter() { }

        public void Leave() { }

        public bool TryEnter(int timeout) { }

        public void SetSpinCount(int count) { }
    }
}
