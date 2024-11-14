#include "pch.h"
#include "OdGeVector2d.h"
#include <cmath>

namespace GeometryNative
{
    /// <summary>
    /// Test suite for the OdGeVector2d class, verifying constructors, vector operations, and properties.
    /// </summary>
    class OdGeVector2dTest : public ::testing::Test
    {
    protected:
        OdGeVector2d vector1;
        OdGeVector2d vector2;

        virtual void SetUp() override
        {
            vector1 = OdGeVector2d(3.0f, 4.0f);
            vector2 = OdGeVector2d(1.0f, 2.0f);
        }
    };

    /// <summary>
    /// DefaultConstructor test verifies that the default constructor initializes the vector to (0, 0).
    /// </summary>
    TEST_F(OdGeVector2dTest, DefaultConstructor)
    {
        OdGeVector2d vector;
        EXPECT_NEAR(vector.x, 0.0f, 1e-6);
        EXPECT_NEAR(vector.y, 0.0f, 1e-6);
    }

    /// <summary>
    /// ParameterizedConstructor test verifies the parameterized constructor initializes the vector with specified x and y values.
    /// </summary>
    /// <param name="vector">Initialized vector with specified x and y coordinates.</param>
    TEST_F(OdGeVector2dTest, ParameterizedConstructor)
    {
        OdGeVector2d vector(1.0f, 2.0f);
        EXPECT_NEAR(vector.x, 1.0f, 1e-6);
        EXPECT_NEAR(vector.y, 2.0f, 1e-6);
    }

    /// <summary>
    /// Length test verifies that the Length method calculates the vector's magnitude.
    /// </summary>
    /// <param name="vector1">Vector for length calculation.</param>
    TEST_F(OdGeVector2dTest, Length)
    {
        float length = vector1.Length();
        EXPECT_NEAR(length, 5.0f, 1e-6);  // Expected length of (3, 4) is 5
    }

    /// <summary>
    /// Normalize test checks if the Normalize method returns a unit vector with a magnitude of 1.
    /// </summary>
    /// <param name="vector1">Vector to normalize.</param>
    TEST_F(OdGeVector2dTest, Normalize)
    {
        OdGeVector2d normalized = vector1.Normalize();
        EXPECT_NEAR(normalized.Length(), 1.0f, 1e-6);
        EXPECT_NEAR(normalized.x, 0.6f, 1e-6);  // Expected x component for (3,4) normalized is 0.6
        EXPECT_NEAR(normalized.y, 0.8f, 1e-6);  // Expected y component for (3,4) normalized is 0.8
    }

    /// <summary>
    /// DotProduct test verifies the dot product calculation between two vectors.
    /// </summary>
    /// <param name="vector1">First vector for dot product calculation.</param>
    /// <param name="vector2">Second vector for dot product calculation.</param>
    TEST_F(OdGeVector2dTest, DotProduct)
    {
        float dotProduct = vector1.DotProduct(vector2);
        EXPECT_NEAR(dotProduct, 11.0f, 1e-6);  // Dot product of (3,4) and (1,2) is 3*1 + 4*2 = 11
    }

    /// <summary>
    /// OperatorPlusEquals test checks if the += operator correctly adds the coordinates of another vector.
    /// </summary>
    /// <param name="vector1">First vector to be incremented by vector2.</param>
    /// <param name="vector2">Vector to add to vector1.</param>
    TEST_F(OdGeVector2dTest, OperatorPlusEquals)
    {
        vector1 += vector2;
        EXPECT_NEAR(vector1.x, 4.0f, 1e-6);
        EXPECT_NEAR(vector1.y, 6.0f, 1e-6);
    }

    /// <summary>
    /// OperatorMinusEquals test verifies that the -= operator correctly subtracts the coordinates of another vector.
    /// </summary>
    /// <param name="vector1">First vector to be decremented by vector2.</param>
    /// <param name="vector2">Vector to subtract from vector1.</param>
    TEST_F(OdGeVector2dTest, OperatorMinusEquals)
    {
        vector1 -= vector2;
        EXPECT_NEAR(vector1.x, 2.0f, 1e-6);
        EXPECT_NEAR(vector1.y, 2.0f, 1e-6);
    }

    /// <summary>
    /// OperatorPlus test checks if the + operator correctly returns the sum of two vectors.
    /// </summary>
    /// <param name="vector1">First vector to add.</param>
    /// <param name="vector2">Second vector to add.</param>
    TEST_F(OdGeVector2dTest, OperatorPlus)
    {
        OdGeVector2d result = vector1 + vector2;
        EXPECT_NEAR(result.x, 4.0f, 1e-6);
        EXPECT_NEAR(result.y, 6.0f, 1e-6);
    }

    /// <summary>
    /// OperatorMinus test verifies that the - operator returns the difference between two vectors.
    /// </summary>
    /// <param name="vector1">First vector to subtract from.</param>
    /// <param name="vector2">Vector to subtract from vector1.</param>
    TEST_F(OdGeVector2dTest, OperatorMinus)
    {
        OdGeVector2d result = vector1 - vector2;
        EXPECT_NEAR(result.x, 2.0f, 1e-6);
        EXPECT_NEAR(result.y, 2.0f, 1e-6);
    }

    /// <summary>
    /// OperatorMultiplyScalar test verifies that the * operator correctly scales the vector by a scalar.
    /// </summary>
    /// <param name="vector1">Vector to be scaled.</param>
    /// <param name="scalar">Scalar multiplier value.</param>
    TEST_F(OdGeVector2dTest, OperatorMultiplyScalar)
    {
        OdGeVector2d result = vector1 * 2.0f;
        EXPECT_NEAR(result.x, 6.0f, 1e-6);
        EXPECT_NEAR(result.y, 8.0f, 1e-6);
    }
}
