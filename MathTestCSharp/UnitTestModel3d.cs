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
    public static class UnitTestModel3d
    {
        [Fact]
        [CommandMethod("TEST_PLANE")]
        public static void Test1()
        {
            MathPlane plane = new MathPlane(new Point3d(0, 0, 0), new Vector3d(0, 0, 1));

            Assert.Equal(new Point3d(0, 0, 0), plane.Origin);

            Assert.Equal(new Vector3d(0, 0, 1), plane.Normal);

            plane.Origin = new Point3d(1, 1, 1);
            Assert.Equal(new Point3d(1, 1, 1), plane.Origin);

            plane.Normal = new Vector3d(1, 0, 0);
            Assert.Equal(new Vector3d(1, 0, 0), plane.Normal);

            plane.Draw();

            MessageBox.Show("TEST_PLANE passed");
        }

        [Fact]
        [CommandMethod("TEST_3DSOLID")]
        public static void Test2()
        {
            Math3dSolid solid1 = new Math3dSolid();
            solid1.createBox(10, 20, 30);
            MessageBox.Show("3D Box created successfully with dimensions 10x20x30.");

            Math3dSolid solid2 = new Math3dSolid();
            Vector3d axis = new Vector3d(0, 0, 1); 
            solid2.createExtrudeSolid(1, 15, axis); 
            MessageBox.Show("Extrude solid created successfully with height 15 along Z-axis.");

            Math3dSolid solid3 = new Math3dSolid();
            solid3.createSweepSolid(2, 3); 
            MessageBox.Show("Sweep solid created successfully with profileId = 2 and pathId = 3.");

            try
            {
                solid1.createBox(-5, 10, 15); 
            }
            catch (ArgumentException ex)
            {
                MessageBox.Show($"Expected error for invalid box dimensions: {ex.Message}");
            }

            try
            {
                Vector3d invalidAxis = new Vector3d(0, 0, 0);
                solid2.createExtrudeSolid(1, 15, invalidAxis);
            }
            catch (ArgumentException ex)
            {
                MessageBox.Show($"Expected error for invalid axis in extrusion: {ex.Message}");
            }

            try
            {
                solid3.createSweepSolid(0, 0); 
            }
            catch (ArgumentException ex)
            {
                MessageBox.Show($"Expected error for invalid profileId and pathId: {ex.Message}");
            }

            MessageBox.Show("TEST_3DSOLID passed");
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
