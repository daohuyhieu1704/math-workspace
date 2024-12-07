#include "pch.h"
#include "OdGePoint2d.h"
#include <cmath>
#include <MathLog.h>

namespace GeometryNative
{
    /// <summary>
    /// Test suite for the OdGePoint2d class, verifying its constructors, methods, and properties.
    /// </summary>
    class OdGePoint2dTest : public ::testing::Test
    {
    protected:
        OdGePoint2d point1;
        OdGePoint2d point2;
        OdGePoint2d origin;

        virtual void SetUp() override
        {
            point1 = OdGePoint2d(1.0f, 2.0f);
            point2 = OdGePoint2d(4.0f, 6.0f);
            origin = OdGePoint2d::kOrigin;
        }
    };

    /// <summary>
    /// DefaultConstructor test verifies that the default constructor initializes the point to (0, 0).
    /// </summary>
    TEST_F(OdGePoint2dTest, DefaultConstructor)
    {
        OdGePoint2d point;
        EXPECT_NEAR(point.x, 0.0f, 1e-6);
        EXPECT_NEAR(point.y, 0.0f, 1e-6);
		MathLog::LogFunction("DefaultConstructor", point);
    }

    /// <summary>
    /// ParameterizedConstructor test validates that the parameterized constructor initializes the point with specified coordinates.
    /// </summary>
    /// <param m_name="point">Initialized point object with specified x and y coordinates.</param>
    TEST_F(OdGePoint2dTest, ParameterizedConstructor)
    {
        OdGePoint2d point(1.0f, 2.0f);
        EXPECT_NEAR(point.x, 1.0f, 1e-6);
        EXPECT_NEAR(point.y, 2.0f, 1e-6);
    }

    /// <summary>
    /// DistanceTo test verifies the calculation of the distance between two points.
    /// </summary>
    /// <param m_name="point1">First point to calculate distance from.</param>
    /// <param m_name="point2">Second point to calculate distance to.</param>
    TEST_F(OdGePoint2dTest, DistanceTo)
    {
        double distance = point1.DistanceTo(point2);
        EXPECT_NEAR(distance, sqrt(25.0), 1e-6);  // Expected distance between (1, 2) and (4, 6) is 5.0
    }

    /// <summary>
    /// StaticOriginPoint test verifies that the static origin point kOrigin is initialized to (0, 0).
    /// </summary>
    /// <param m_name="origin">Static origin point to be checked.</param>
    TEST_F(OdGePoint2dTest, StaticOriginPoint)
    {
        EXPECT_NEAR(origin.x, 0.0f, 1e-6);
        EXPECT_NEAR(origin.y, 0.0f, 1e-6);
    }
}
