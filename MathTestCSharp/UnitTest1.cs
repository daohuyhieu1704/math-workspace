using MathUI.Commands;
using System.Windows;

namespace MathTestCSharp
{
    public static class UnitTest1
    {
        [Fact]
        [CommandMethod("TEST_SUITE_SCALE")]
        public static void Test1()
        {
            Assert.True(true);
            MessageBox.Show("Test1");
        }
    }
}