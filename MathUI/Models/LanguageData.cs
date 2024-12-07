using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathUI.Models
{
    public class LanguageData
    {
        public LanguageData(string name, string twoLetterIso)
        {
            Name = name;
            TwoLetterIso = twoLetterIso;
        }

        public string Name { get; set; }
        public string TwoLetterIso { get; set; }
    }
}
