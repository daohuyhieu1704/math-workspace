#include "pch.h"
#include "OdGeVector3d.h"
#include <cmath>

namespace GeometryNative
{
    /// <summary>
    /// Test suite for the OdGeVector3d class, verifying constructors, vector operations, and properties.
    /// </summary>
    class OdGeVector3dTest : public ::testing::Test
    {
    protected:
        OdGeVector3d vector1;
        OdGeVector3d vector2;

        virtual void SetUp() override
        {
            vector1 = OdGeVector3d(3.0f, 4.0f, 5.0f);
            vector2 = OdGeVector3d(1.0f, 2.0f, 3.0f);
        }
    };

    /// <summary>
    /// DefaultConstructor test verifies that the default constructor initializes the vector to (0, 0, 0).
    /// </summary>
    TEST_F(OdGeVector3dTest, DefaultConstructor)
    {
        OdGeVector3d vector;
        EXPECT_NEAR(vector.x, 0.0f, 1e-6);
        EXPECT_NEAR(vector.y, 0.0f, 1e-6);
        EXPECT_NEAR(vector.z, 0.0f, 1e-6);
    }

    /// <summary>
    /// ParameterizedConstructor test verifies that the parameterized constructor initializes the vector with specified x, y, and z values.
    /// </summary>
    TEST_F(OdGeVector3dTest, ParameterizedConstructor)
    {
        OdGeVector3d vector(1.0f, 2.0f, 3.0f);
        EXPECT_NEAR(vector.x, 1.0f, 1e-6);
        EXPECT_NEAR(vector.y, 2.0f, 1e-6);
        EXPECT_NEAR(vector.z, 3.0f, 1e-6);
    }

    /// <summary>
    /// Length test verifies that the Length method calculates the vector's magnitude.
    /// </summary>
    TEST_F(OdGeVector3dTest, Length)
    {
        float length = vector1.Length();
        EXPECT_NEAR(length, sqrt(50.0f), 1e-6);  // Expected length of (3, 4, 5) is sqrt(3^2 + 4^2 + 5^2) = sqrt(50)
    }

    /// <summary>
    /// Normalize test checks if the Normalize method returns a unit vector with a magnitude of 1.
    /// </summary>
    TEST_F(OdGeVector3dTest, Normalize)
    {
        OdGeVector3d normalized = vector1.Normalize();
        EXPECT_NEAR(normalized.Length(), 1.0f, 1e-6);
    }

    /// <summary>
    /// CrossProduct test verifies the calculation of the cross product between two vectors.
    /// </summary>
    TEST_F(OdGeVector3dTest, CrossProduct)
    {
        OdGeVector3d crossProduct = vector1.CrossProduct(vector2);
        EXPECT_NEAR(crossProduct.x, 2.0f, 1e-6);
        EXPECT_NEAR(crossProduct.y, -4.0f, 1e-6);
        EXPECT_NEAR(crossProduct.z, 2.0f, 1e-6);
    }

    /// <summary>
    /// DotProduct test verifies the dot product calculation between two vectors.
    /// </summary>
    TEST_F(OdGeVector3dTest, DotProduct)
    {
        float dotProduct = vector1.DotProduct(vector2);
        EXPECT_NEAR(dotProduct, 26.0f, 1e-6);  // Dot product of (3,4,5) and (1,2,3) is 3*1 + 4*2 + 5*3 = 26
    }

    /// <summary>
    /// OperatorNegate test verifies that the - operator negates each component of the vector.
    /// </summary>
    TEST_F(OdGeVector3dTest, OperatorNegate)
    {
        OdGeVector3d negated = -vector1;
        EXPECT_NEAR(negated.x, -3.0f, 1e-6);
        EXPECT_NEAR(negated.y, -4.0f, 1e-6);
        EXPECT_NEAR(negated.z, -5.0f, 1e-6);
    }

    /// <summary>
    /// OperatorPlusEquals test checks if the += operator correctly adds the coordinates of another vector.
    /// </summary>
    TEST_F(OdGeVector3dTest, OperatorPlusEquals)
    {
        vector1 += vector2;
        EXPECT_NEAR(vector1.x, 4.0f, 1e-6);
        EXPECT_NEAR(vector1.y, 6.0f, 1e-6);
        EXPECT_NEAR(vector1.z, 8.0f, 1e-6);
    }

    /// <summary>
    /// OperatorMinusEquals test verifies that the -= operator correctly subtracts the coordinates of another vector.
    /// </summary>
    TEST_F(OdGeVector3dTest, OperatorMinusEquals)
    {
        vector1 -= vector2;
        EXPECT_NEAR(vector1.x, 2.0f, 1e-6);
        EXPECT_NEAR(vector1.y, 2.0f, 1e-6);
        EXPECT_NEAR(vector1.z, 2.0f, 1e-6);
    }

    /// <summary>
    /// OperatorPlus test checks if the + operator correctly returns the sum of two vectors.
    /// </summary>
    TEST_F(OdGeVector3dTest, OperatorPlus)
    {
        OdGeVector3d result = vector1 + vector2;
        EXPECT_NEAR(result.x, 4.0f, 1e-6);
        EXPECT_NEAR(result.y, 6.0f, 1e-6);
        EXPECT_NEAR(result.z, 8.0f, 1e-6);
    }

    /// <summary>
    /// OperatorMinus test verifies that the - operator returns the difference between two vectors.
    /// </summary>
    TEST_F(OdGeVector3dTest, OperatorMinus)
    {
        OdGeVector3d result = vector1 - vector2;
        EXPECT_NEAR(result.x, 2.0f, 1e-6);
        EXPECT_NEAR(result.y, 2.0f, 1e-6);
        EXPECT_NEAR(result.z, 2.0f, 1e-6);
    }

    /// <summary>
    /// OperatorMultiplyScalar test verifies that the * operator correctly scales the vector by a scalar.
    /// </summary>
    TEST_F(OdGeVector3dTest, OperatorMultiplyScalar)
    {
        OdGeVector3d result = vector1 * 2.0f;
        EXPECT_NEAR(result.x, 6.0f, 1e-6);
        EXPECT_NEAR(result.y, 8.0f, 1e-6);
        EXPECT_NEAR(result.z, 10.0f, 1e-6);
    }

    /// <summary>
    /// OperatorDivideEquals test checks that the /= operator scales the vector by the reciprocal of a scalar.
    /// </summary>
    TEST_F(OdGeVector3dTest, OperatorDivideEquals)
    {
        vector1 /= 2.0f;
        EXPECT_NEAR(vector1.x, 1.5f, 1e-6);
        EXPECT_NEAR(vector1.y, 2.0f, 1e-6);
        EXPECT_NEAR(vector1.z, 2.5f, 1e-6);
    }

    /// <summary>
    /// IsEqual test confirms that IsEqual method returns true if two vectors are nearly equal within a tolerance.
    /// </summary>
    TEST_F(OdGeVector3dTest, IsEqual)
    {
        OdGeVector3d vector3(3.0f, 4.0f, 5.0f);
        EXPECT_TRUE(vector1.IsEqual(vector3));
        EXPECT_FALSE(vector1.IsEqual(vector2));
    }
}
