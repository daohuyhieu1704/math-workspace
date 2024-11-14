#include "pch.h"
#include "OdGeScale3d.h"
#include <cmath>

namespace GeometryNative
{
    /// <summary>
    /// Test suite for the OdGeScale3d class, verifying constructors, operators, and transformations.
    /// </summary>
    class OdGeScale3dTest : public ::testing::Test
    {
    protected:
        OdGeScale3d scale1;
        OdGeScale3d scale2;

        virtual void SetUp() override
        {
            scale1 = OdGeScale3d(2.0, 3.0, 4.0);
            scale2 = OdGeScale3d(1.5, 2.5, 3.5);
        }
    };

    /// <summary>
    /// DefaultConstructor test verifies that the default constructor initializes the scale factors to (1, 1, 1).
    /// </summary>
    TEST_F(OdGeScale3dTest, DefaultConstructor)
    {
        OdGeScale3d scale;
        EXPECT_NEAR(scale[0], 1.0, 1e-6);
        EXPECT_NEAR(scale[1], 1.0, 1e-6);
        EXPECT_NEAR(scale[2], 1.0, 1e-6);
    }

    /// <summary>
    /// UniformConstructor test verifies the constructor with a uniform scale factor.
    /// </summary>
    TEST_F(OdGeScale3dTest, UniformConstructor)
    {
        OdGeScale3d scale(2.0);
        EXPECT_NEAR(scale[0], 2.0, 1e-6);
        EXPECT_NEAR(scale[1], 2.0, 1e-6);
        EXPECT_NEAR(scale[2], 2.0, 1e-6);
    }

    /// <summary>
    /// ParameterizedConstructor test verifies the constructor with individual scale factors for each axis.
    /// </summary>
    TEST_F(OdGeScale3dTest, ParameterizedConstructor)
    {
        OdGeScale3d scale(2.0, 3.0, 4.0);
        EXPECT_NEAR(scale[0], 2.0, 1e-6);
        EXPECT_NEAR(scale[1], 3.0, 1e-6);
        EXPECT_NEAR(scale[2], 4.0, 1e-6);
    }

    /// <summary>
    /// OperatorMultiplyScale test verifies multiplication of two scale objects.
    /// </summary>
    TEST_F(OdGeScale3dTest, OperatorMultiplyScale)
    {
        OdGeScale3d result = scale1 * scale2;
        EXPECT_NEAR(result[0], 3.0, 1e-6);
        EXPECT_NEAR(result[1], 7.5, 1e-6);
        EXPECT_NEAR(result[2], 14.0, 1e-6);
    }

    /// <summary>
    /// OperatorMultiplyScalar test verifies multiplication of a scale by a scalar.
    /// </summary>
    TEST_F(OdGeScale3dTest, OperatorMultiplyScalar)
    {
        OdGeScale3d result = scale1 * 2.0;
        EXPECT_NEAR(result[0], 4.0, 1e-6);
        EXPECT_NEAR(result[1], 6.0, 1e-6);
        EXPECT_NEAR(result[2], 8.0, 1e-6);
    }

    /// <summary>
    /// OperatorMultiplyScalarFriend test verifies scalar multiplication using the friend function.
    /// </summary>
    TEST_F(OdGeScale3dTest, OperatorMultiplyScalarFriend)
    {
        OdGeScale3d result = 2.0 * scale1;
        EXPECT_NEAR(result[0], 4.0, 1e-6);
        EXPECT_NEAR(result[1], 6.0, 1e-6);
        EXPECT_NEAR(result[2], 8.0, 1e-6);
    }

    /// <summary>
    /// OperatorEqualEqual test checks if two scale objects with the same factors are considered equal.
    /// </summary>
    TEST_F(OdGeScale3dTest, OperatorEqualEqual)
    {
        OdGeScale3d scale3(2.0, 3.0, 4.0);
        EXPECT_TRUE(scale1 == scale3);
        EXPECT_FALSE(scale1 == scale2);
    }

    /// <summary>
    /// OperatorNotEqual test checks if two scale objects with different factors are considered not equal.
    /// </summary>
    TEST_F(OdGeScale3dTest, OperatorNotEqual)
    {
        EXPECT_TRUE(scale1 != scale2);
    }

    /// <summary>
    /// Inverse test verifies the inverse of a scale object.
    /// </summary>
    TEST_F(OdGeScale3dTest, Inverse)
    {
        OdGeScale3d inverse = scale1.inverse();
        EXPECT_NEAR(inverse[0], 1.0 / 2.0, 1e-6);
        EXPECT_NEAR(inverse[1], 1.0 / 3.0, 1e-6);
        EXPECT_NEAR(inverse[2], 1.0 / 4.0, 1e-6);
    }

    /// <summary>
    /// IsProportional test verifies if the scale factors are proportional (same ratios).
    /// </summary>
    TEST_F(OdGeScale3dTest, IsProportional)
    {
        OdGeScale3d proportionalScale(2.0, 4.0, 6.0);
        EXPECT_TRUE(proportionalScale.isProportional(1e-6));

        OdGeScale3d nonProportionalScale(2.0, 3.0, 4.0);
        EXPECT_FALSE(nonProportionalScale.isProportional(1e-6));
    }

    /// <summary>
    /// IsEqualTo test checks if two scale objects are equal within a given tolerance.
    /// </summary>
    TEST_F(OdGeScale3dTest, IsEqualTo)
    {
        OdGeScale3d scale3(2.000000001, 3.000000001, 4.000000001);
        EXPECT_TRUE(scale1.isEqualTo(scale3, 1e-8));
    }

    /// <summary>
    /// Set test sets the scale factors to specific values and verifies them.
    /// </summary>
    TEST_F(OdGeScale3dTest, Set)
    {
        scale1.set(5.0, 6.0, 7.0);
        EXPECT_NEAR(scale1[0], 5.0, 1e-6);
        EXPECT_NEAR(scale1[1], 6.0, 1e-6);
        EXPECT_NEAR(scale1[2], 7.0, 1e-6);
    }

    /// <summary>
    /// OperatorIndexing test verifies that indexing operators return correct scale factors.
    /// </summary>
    TEST_F(OdGeScale3dTest, OperatorIndexing)
    {
        EXPECT_NEAR(scale1[0], 2.0, 1e-6);
        EXPECT_NEAR(scale1[1], 3.0, 1e-6);
        EXPECT_NEAR(scale1[2], 4.0, 1e-6);
    }

    /// <summary>
    /// IsUniform test checks if the scale vector is uniform (equal factors on all axes).
    /// </summary>
    TEST_F(OdGeScale3dTest, IsUniform)
    {
        OdGeScale3d uniformScale(3.0, 3.0, 3.0);
        EXPECT_TRUE(uniformScale.isProportional());
        EXPECT_FALSE(scale1.isProportional());
    }

    /// <summary>
    /// IsValid test verifies if the scale vector has valid factors (non-zero).
    /// </summary>
    TEST_F(OdGeScale3dTest, IsValid)
    {
        EXPECT_TRUE(scale1.isValid());
        OdGeScale3d invalidScale(0.0, 3.0, 4.0);
        EXPECT_FALSE(invalidScale.isValid());
    }
}
