using MathGL;
using MathUI.Commands;
using Geometry;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace MathTestCSharp
{
    public static class UnitTestModel2d
    {
        [Fact]
        [CommandMethod("TEST_LINE")]
        public static void Test1()
        {
            MathLine mathLine1 = new(new Point3d(0, 0, 0), new Point3d(10, 0, 0));
            mathLine1.Draw();
            Assert.Equal(new Point3d(0, 0, 0), mathLine1.StartPnt);
            Assert.Equal(new Point3d(10, 0, 0), mathLine1.EndPnt);

            MathLine mathLine2 = new(new Point3d(1, 1, 0), new Point3d(4, 5, 0));
            mathLine2.Draw();
            Assert.Equal(new Point3d(1, 1, 0), mathLine2.StartPnt);
            Assert.Equal(new Point3d(4, 5, 0), mathLine2.EndPnt);

            MessageBox.Show("TEST_LINE passed");
        }

        [Fact]
        [CommandMethod("TEST_CIRCLE")]
        public static void Test2()
        {
            MathCircle mathCircle1 = new(Point3d.Origin, 5);
            mathCircle1.Draw();
            Assert.Equal(5, mathCircle1.Radius);

            //// Test case 2: Vẽ đường tròn với bán kính bằng 0
            MathCircle mathCircle2 = new(Point3d.Origin, 0);
            mathCircle2.Draw();
            Assert.Equal(0, mathCircle2.Radius);

            MessageBox.Show("TEST_CIRCLE passed");
        }

        [Fact]
        [CommandMethod("TEST_ARC")]
        public static void Test3()
        {
            MathArc mathArc1 = new(new Point3d(0, 0, 0), new Point3d(5, 5, 0));
            mathArc1.Draw();
            Assert.Equal(new Point3d(0, 0, 0), mathArc1.StartPnt);
            Assert.Equal(new Point3d(5, 5, 0), mathArc1.EndPnt);

            MathArc mathArc2 = new(new Point3d(0, 0, 0), new Point3d(5, 0, 0), new Point3d(2.5, 2.5, 0));
            mathArc2.Draw();
            Assert.Equal(new Point3d(0, 0, 0), mathArc2.StartPnt);
            Assert.Equal(new Point3d(5, 0, 0), mathArc2.EndPnt);

            MessageBox.Show("TEST_DRAW_ARC passed");
        }

        [Fact]
        [CommandMethod("TEST_POLYLINE")]
        public static void Test4()
        {
            MathPolyline polyline = new();
            polyline.AddVertex(new Point3d(0, 0, 0));
            polyline.AddVertex(new Point3d(5, 0, 0), 0.5);
            polyline.AddVertex(new Point3d(5, 5, 0));

            Assert.Equal(3, polyline.NumVerts);
            Assert.Equal(new Point3d(5, 0, 0), polyline.GetVertexAt(1));
            Assert.Equal(0.5, polyline.GetBulgeAt(1));

            polyline.IsClosed = true;
            Assert.True(polyline.IsClosed);

            polyline.Draw();
            MessageBox.Show("TEST_POLYLINE passed");
        }

        [Fact]
        [CommandMethod("TEST_2D")]
        public static void TestAll()
        {
            Test1();
            Test2();
            Test3();
            Test4();
        }
    }
}
