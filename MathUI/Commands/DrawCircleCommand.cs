using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathUI.Commands
{
    public class DrawCircleCommand
    {
        [CommandMethod("CIRCLE")]
        public static void DrawCircle()
        {
            Console.WriteLine("Drawing a circle...");
        }
    }
}
