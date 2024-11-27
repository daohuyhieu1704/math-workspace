#include "pch.h"
#include "OdGePlane.h"
#include "OdGePoint3d.h"
#include "OdGeVector3d.h"
#include <cmath>
#include <MathLog.h>

namespace GeometryNative
{
    /// <summary>
    /// Test suite for the OdGePlane class, verifying its constructors, methods, and properties.
    /// </summary>
    class OdGePlaneTest : public ::testing::Test
    {
    protected:
        OdGePlane plane1;
        OdGePlane plane2;
        OdGePoint3d pointOnPlane;
        OdGeVector3d normal;

        virtual void SetUp() override
        {
            pointOnPlane = OdGePoint3d(1.0, 2.0, 3.0);
            normal = OdGeVector3d(0.0, 0.0, 1.0);
            plane1 = OdGePlane(pointOnPlane, normal); // Constructing a plane passing through (1, 2, 3) with a Z-axis normal
            plane2 = OdGePlane(OdGePoint3d(0.0, 0.0, 0.0), OdGeVector3d(1.0, 0.0, 0.0)); // Another plane along the X-axis
        }
    };

    /// <summary>
    /// DefaultConstructor test verifies that the default constructor initializes the plane to a valid state.
    /// </summary>
    TEST_F(OdGePlaneTest, DefaultConstructor)
    {
        OdGePlane plane;
        EXPECT_NEAR(plane.normal.Length(), 1.0, 1e-6); // Assuming default normal is unit length
        EXPECT_NEAR(plane.DistanceTo(OdGePoint3d::kOrigin), 0.0, 1e-6);
        MathLog::LogFunction("DefaultConstructor", plane);
    }

    /// <summary>
    /// ParameterizedConstructor test validates that the parameterized constructor initializes the plane with specified point and normal.
    /// </summary>
    TEST_F(OdGePlaneTest, ParameterizedConstructor)
    {
        EXPECT_NEAR(plane1.normal.x, normal.x, 1e-6);
        EXPECT_NEAR(plane1.normal.y, normal.y, 1e-6);
        EXPECT_NEAR(plane1.normal.z, normal.z, 1e-6);
        EXPECT_NEAR(plane1.DistanceTo(pointOnPlane), 0.0, 1e-6); // Point lies on the plane
    }

    /// <summary>
    /// DistanceTo test verifies the calculation of the shortest distance between the plane and a point.
    /// </summary>
    TEST_F(OdGePlaneTest, DistanceTo)
    {
        OdGePoint3d testPoint(1.0, 2.0, 5.0);
        double distance = plane1.DistanceTo(testPoint);
        EXPECT_NEAR(distance, 2.0, 1e-6); // Expected perpendicular distance
    }

    /// <summary>
    /// NormalDirection test verifies that the normal vector of the plane is calculated correctly.
    /// </summary>
    TEST_F(OdGePlaneTest, NormalDirection)
    {
        EXPECT_NEAR(plane1.normal.x, 0.0, 1e-6);
        EXPECT_NEAR(plane1.normal.y, 0.0, 1e-6);
        EXPECT_NEAR(plane1.normal.z, 1.0, 1e-6); // Z-axis normal for plane1
    }

    /// <summary>
    /// ParallelPlane test checks if two planes are parallel by comparing their normal vectors.
    /// </summary>
    TEST_F(OdGePlaneTest, ParallelPlane)
    {
        OdGePlane parallelPlane(OdGePoint3d(1.0, 1.0, 4.0), normal);
        EXPECT_TRUE(plane1.normal.isParallelTo(parallelPlane.normal));
    }

    /// <summary>
    /// Intersect test checks if two planes intersect and returns the intersection line or result.
    /// </summary>
    TEST_F(OdGePlaneTest, Intersect)
    {
        // Assuming Intersect() returns a line or boolean indicating intersection
		OdGePoint3d pointOnLine;
		OdGeVector3d lineDirection;
        bool intersects = plane1.Intersect(plane2, pointOnLine, lineDirection);
        EXPECT_TRUE(intersects); // Expecting planes to intersect
    }
}
