using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathUI.ViewModels
{
    internal class Command
    {
        private string title = String.Empty;

        public string Title
        {
            get { return title; }
            set
            {
                if (title != value)
                {
                    title = value;
                }
            }

        }
    }
}
