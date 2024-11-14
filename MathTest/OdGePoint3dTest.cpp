#include "pch.h"
#include "OdGePoint3d.h"
#include "OdGeVector3d.h"
#include "OdGePoint2d.h"
#include <cmath>

namespace GeometryNative
{
    /// <summary>
    /// Test suite for the OdGePoint3d class, verifying its constructors, methods, and operators.
    /// </summary>
    class OdGePoint3dTest : public ::testing::Test
    {
    protected:
        OdGePoint3d point1;
        OdGePoint3d point2;
        OdGePoint3d origin;

        virtual void SetUp() override
        {
            point1 = OdGePoint3d(1.0f, 2.0f, 3.0f);
            point2 = OdGePoint3d(4.0f, 5.0f, 6.0f);
            origin = OdGePoint3d::kOrigin;
        }
    };

    /// <summary>
    /// DefaultConstructor test validates the default constructor initializes coordinates to (0, 0, 0).
    /// </summary>
    TEST_F(OdGePoint3dTest, DefaultConstructor)
    {
        OdGePoint3d point;
        EXPECT_NEAR(point.x, 0.0f, 1e-6);
        EXPECT_NEAR(point.y, 0.0f, 1e-6);
        EXPECT_NEAR(point.z, 0.0f, 1e-6);
    }

    /// <summary>
    /// ParameterizedConstructor test validates the parameterized constructor initializes the point with given coordinates.
    /// </summary>
    /// <param name="point">Initialized point object with specified coordinates.</param>
    TEST_F(OdGePoint3dTest, ParameterizedConstructor)
    {
        OdGePoint3d point(1.0f, 2.0f, 3.0f);
        EXPECT_NEAR(point.x, 1.0f, 1e-6);
        EXPECT_NEAR(point.y, 2.0f, 1e-6);
        EXPECT_NEAR(point.z, 3.0f, 1e-6);
    }

    /// <summary>
    /// DistanceTo test verifies the distance calculation between two points.
    /// </summary>
    /// <param name="point1">First point to calculate distance from.</param>
    /// <param name="point2">Second point to calculate distance to.</param>
    TEST_F(OdGePoint3dTest, DistanceTo)
    {
        double distance = point1.DistanceTo(point2);
        EXPECT_NEAR(distance, sqrt(27.0f), 1e-6);
    }

    /// <summary>
    /// ConvertTo2d test verifies the conversion of 3D point coordinates to a 2D point.
    /// </summary>
    /// <param name="point1">Point to be converted to 2D.</param>
    TEST_F(OdGePoint3dTest, ConvertTo2d)
    {
        OdGePoint2d point2d = point1.ConvertTo2d();
        EXPECT_NEAR(point2d.x, point1.x, 1e-6);
        EXPECT_NEAR(point2d.y, point1.y, 1e-6);
    }

    /// <summary>
    /// CenterTo test calculates and verifies the midpoint between two points.
    /// </summary>
    /// <param name="point1">First point to calculate midpoint from.</param>
    /// <param name="point2">Second point to calculate midpoint to.</param>
    TEST_F(OdGePoint3dTest, CenterTo)
    {
        OdGePoint3d center = point1.CenterTo(point2);
        EXPECT_NEAR(center.x, 2.5f, 1e-6);
        EXPECT_NEAR(center.y, 3.5f, 1e-6);
        EXPECT_NEAR(center.z, 4.5f, 1e-6);
    }

    /// <summary>
    /// OperatorPlusEqualsPoint3d test checks if += operator correctly adds coordinates of two points.
    /// </summary>
    /// <param name="point1">First point to be incremented by point2.</param>
    /// <param name="point2">Second point to increment point1.</param>
    TEST_F(OdGePoint3dTest, OperatorPlusEqualsPoint3d)
    {
        point1 += point2;
        EXPECT_NEAR(point1.x, 5.0f, 1e-6);
        EXPECT_NEAR(point1.y, 7.0f, 1e-6);
        EXPECT_NEAR(point1.z, 9.0f, 1e-6);
    }

    /// <summary>
    /// OperatorPlusEqualsVector3d test verifies += operator adds a vector to a point correctly.
    /// </summary>
    /// <param name="point1">Point to add vector coordinates to.</param>
    /// <param name="vec">Vector to be added to point1.</param>
    TEST_F(OdGePoint3dTest, OperatorPlusEqualsVector3d)
    {
        OdGeVector3d vec(1.0f, 1.0f, 1.0f);
        point1 += vec;
        EXPECT_NEAR(point1.x, 2.0f, 1e-6);
        EXPECT_NEAR(point1.y, 3.0f, 1e-6);
        EXPECT_NEAR(point1.z, 4.0f, 1e-6);
    }

    /// <summary>
    /// OperatorEqualEqual test checks if == operator accurately compares two points for equality.
    /// </summary>
    /// <param name="point1">Point for comparison.</param>
    /// <param name="point3">Point identical to point1 for positive comparison.</param>
    /// <param name="point2">Different point to confirm inequality.</param>
    TEST_F(OdGePoint3dTest, OperatorEqualEqual)
    {
        OdGePoint3d point3(1.0f, 2.0f, 3.0f);
        EXPECT_TRUE(point1 == point3);
        EXPECT_FALSE(point1 == point2);
    }

    /// <summary>
    /// OperatorMultiplyScalar test verifies that multiplying a point by a scalar scales its coordinates.
    /// </summary>
    /// <param name="point1">Point to be multiplied by a scalar.</param>
    /// <param name="scalar">Scalar multiplier value.</param>
    TEST_F(OdGePoint3dTest, OperatorMultiplyScalar)
    {
        OdGePoint3d point = point1 * 2.0f;
        EXPECT_NEAR(point.x, 2.0f, 1e-6);
        EXPECT_NEAR(point.y, 4.0f, 1e-6);
        EXPECT_NEAR(point.z, 6.0f, 1e-6);
    }

    /// <summary>
    /// OperatorPlusPoint3d test validates the addition operator correctly sums two points.
    /// </summary>
    /// <param name="point1">First point to add.</param>
    /// <param name="point2">Second point to add.</param>
    TEST_F(OdGePoint3dTest, OperatorPlusPoint3d)
    {
        OdGePoint3d point = point1 + point2;
        EXPECT_NEAR(point.x, 5.0f, 1e-6);
        EXPECT_NEAR(point.y, 7.0f, 1e-6);
        EXPECT_NEAR(point.z, 9.0f, 1e-6);
    }

    /// <summary>
    /// OperatorPlusVector3d test checks the addition of a vector to a point.
    /// </summary>
    /// <param name="point1">Point to add the vector to.</param>
    /// <param name="vec">Vector to be added to the point.</param>
    TEST_F(OdGePoint3dTest, OperatorPlusVector3d)
    {
        OdGeVector3d vec(1.0f, 2.0f, 3.0f);
        OdGePoint3d result = point1 + vec;
        EXPECT_NEAR(result.x, 2.0f, 1e-6);
        EXPECT_NEAR(result.y, 4.0f, 1e-6);
        EXPECT_NEAR(result.z, 6.0f, 1e-6);
    }

    /// <summary>
    /// OperatorMinusPoint3d test verifies that subtracting two points yields a correct vector.
    /// </summary>
    /// <param name="point2">Point to subtract from.</param>
    /// <param name="point1">Point to subtract.</param>
    TEST_F(OdGePoint3dTest, OperatorMinusPoint3d)
    {
        OdGeVector3d vec = point2 - point1;
        EXPECT_NEAR(vec.x, 3.0f, 1e-6);
        EXPECT_NEAR(vec.y, 3.0f, 1e-6);
        EXPECT_NEAR(vec.z, 3.0f, 1e-6);
    }

    /// <summary>
    /// IsEqual test confirms IsEqual method returns true if two points are nearly equal, false otherwise.
    /// </summary>
    /// <param name="point11">First point for comparison.</param>
    /// <param name="point12">Second point close to point11 for equality check.</param>
    TEST_F(OdGePoint3dTest, IsEqual)
    {
        OdGePoint3d point11(1.000001f, 2.000001f, 3.000001f);
        OdGePoint3d point12(1.0f, 2.0f, 3.0f);
        EXPECT_TRUE(point11.IsEqual(point12));
        EXPECT_FALSE(point11.IsEqual(point2));
    }

    /// <summary>
    /// StaticOriginPoint test verifies the static origin point kOrigin is initialized to (0, 0, 0).
    /// </summary>
    /// <param name="origin">Static origin point to be checked.</param>
    TEST_F(OdGePoint3dTest, StaticOriginPoint)
    {
        EXPECT_NEAR(origin.x, 0.0f, 1e-6);
        EXPECT_NEAR(origin.y, 0.0f, 1e-6);
        EXPECT_NEAR(origin.z, 0.0f, 1e-6);
    }
}