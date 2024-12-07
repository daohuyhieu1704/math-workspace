using MathUI.Commands;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathTestCSharp
{
    public static class UnitTestModel3d
    {
        [Fact]
        public static void Test1()
        {
        }

        [Fact]
        public static void Test2()
        {
        }

        [Fact]
        public static void Test3()
        {
        }

        [Fact]
        [CommandMethod("TEST_3D")]
        public static void TestAll()
        {
            Test1();
            Test2();
            Test3();
        }
    }
}
