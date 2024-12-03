using Geometry;
using MathGL;
using MathUI.Commands;
using System.Windows;

namespace MathTestCSharp
{
    public static class UnitTestTransform
    {
        [Fact]
        [CommandMethod("TEST_SCALE")]
        public static void Test1()
        {
            //// Test case 1
            MathCircle mathCircle1 = new(Point3d.Origin, 4)
            {
                Scale = new Scale3d(2)
            };
            mathCircle1.Draw();
            Assert.Equal(8, mathCircle1.Radius);

            //// Test case 2
            MathCircle mathCircle2 = new(Point3d.Origin, 4)
            {
                Scale = new Scale3d(0.5)
            };
            mathCircle2.Draw();
            Assert.Equal(2, mathCircle2.Radius);
            MessageBox.Show("TEST_SCALE passed");
        }
    }
}