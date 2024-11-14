#include "pch.h"
#include "OdGeMatrix3d.h"
#include "OdGeVector3d.h"
#include "OdGePoint3d.h"
#include <cmath>

namespace Geometry
{
    /// <summary>
    /// Test suite for the OdGeMatrix3d class, verifying constructors, matrix operations, and properties.
    /// </summary>
    class OdGeMatrix3dTest : public ::testing::Test
    {
    protected:
        OdGeMatrix3d matrix1;
        OdGeMatrix3d matrix2;

        virtual void SetUp() override
        {
            matrix1.setToIdentity();
            matrix2 = OdGeMatrix3d::kIdentity;
        }
    };

    /// <summary>
    /// IdentityMatrix test verifies that setToIdentity initializes the matrix as an identity matrix.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, IdentityMatrix)
    {
        matrix1.setToIdentity();
        EXPECT_TRUE(matrix1 == OdGeMatrix3d::kIdentity);
    }

    /// <summary>
    /// OperatorMultiplyMatrix test checks the multiplication of two matrices.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, OperatorMultiplyMatrix)
    {
        OdGeMatrix3d result = matrix1 * matrix2;
        EXPECT_TRUE(result == OdGeMatrix3d::kIdentity);
    }

    /// <summary>
    /// PreMultBy test verifies pre-multiplication of a matrix.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, PreMultBy)
    {
        matrix1.preMultBy(matrix2);
        EXPECT_TRUE(matrix1 == OdGeMatrix3d::kIdentity);
    }

    /// <summary>
    /// PostMultBy test verifies post-multiplication of a matrix.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, PostMultBy)
    {
        matrix1.postMultBy(matrix2);
        EXPECT_TRUE(matrix1 == OdGeMatrix3d::kIdentity);
    }

    /// <summary>
    /// Determinant test calculates the determinant of a 3x3 submatrix.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, Determinant)
    {
        double sample[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
        double det = matrix1.det3x3(sample);
        EXPECT_NEAR(det, 0.0, 1e-6);
    }

    /// <summary>
    /// InvertMatrix test checks the inversion of a non-singular matrix.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, InvertMatrix)
    {
        OdGeMatrix3d nonSingularMatrix = OdGeMatrix3d::kIdentity;
        nonSingularMatrix(0, 0) = 2.0;
        OdGeMatrix3d inverseMatrix = nonSingularMatrix.inverse();
        OdGeMatrix3d identityCheck = nonSingularMatrix * inverseMatrix;
        EXPECT_TRUE(identityCheck.isEqualTo(OdGeMatrix3d::kIdentity));
    }

    /// <summary>
    /// IsSingular test verifies that a matrix is identified as singular if it has zero determinant.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, IsSingular)
    {
        OdGeMatrix3d singularMatrix;
        singularMatrix(0, 0) = 0.0;
        singularMatrix(1, 1) = 0.0;
        EXPECT_TRUE(singularMatrix.isSingular());
    }

    /// <summary>
    /// TransposeMatrix test checks the transposition of a matrix.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, TransposeMatrix)
    {
        matrix1(0, 1) = 3.0;
        matrix1(1, 0) = 5.0;
        OdGeMatrix3d transposed = matrix1.transpose();
        EXPECT_NEAR(transposed(0, 1), 5.0, 1e-6);
        EXPECT_NEAR(transposed(1, 0), 3.0, 1e-6);
    }

    /// <summary>
    /// OperatorEqualEqual test checks if two identical matrices are considered equal.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, OperatorEqualEqual)
    {
        EXPECT_TRUE(matrix1 == matrix2);
    }

    /// <summary>
    /// OperatorNotEqual test verifies if two different matrices are considered not equal.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, OperatorNotEqual)
    {
        matrix1(0, 0) = 2.0;
        EXPECT_TRUE(matrix1 != matrix2);
    }

    /// <summary>
    /// SetTranslation test sets a translation in the matrix and verifies the translation vector.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, SetTranslation)
    {
        OdGeVector3d translationVector(1.0, 2.0, 3.0);
        matrix1.setTranslation(translationVector);
        OdGeVector3d resultTranslation = matrix1.translation();
        EXPECT_NEAR(resultTranslation.x, 1.0, 1e-6);
        EXPECT_NEAR(resultTranslation.y, 2.0, 1e-6);
        EXPECT_NEAR(resultTranslation.z, 3.0, 1e-6);
    }

    /// <summary>
    /// SetScaling test applies scaling transformation and verifies matrix scaling.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, SetScaling)
    {
        OdGePoint3d center(1.0, 1.0, 1.0);
        matrix1.setToScaling(2.0, center);
        EXPECT_NEAR(matrix1(0, 0), 2.0, 1e-6);
        EXPECT_NEAR(matrix1(1, 1), 2.0, 1e-6);
        EXPECT_NEAR(matrix1(2, 2), 2.0, 1e-6);
    }

    /// <summary>
    /// SetRotation test applies rotation transformation and verifies matrix rotation.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, SetRotation)
    {
        OdGeVector3d axis(0.0, 0.0, 1.0);
        matrix1.setToRotation(3.14 / 2, axis);
        OdGeMatrix3d expectedRotation;
        expectedRotation(0, 0) = 0.0;
        expectedRotation(0, 1) = -1.0;
        expectedRotation(1, 0) = 1.0;
        expectedRotation(1, 1) = 0.0;
        expectedRotation(2, 2) = 1.0;
        expectedRotation(3, 3) = 1.0;
        EXPECT_TRUE(matrix1.isEqualTo(expectedRotation, 1e-6));
    }

    /// <summary>
    /// IsEqualTo test checks if two matrices are nearly equal within a tolerance.
    /// </summary>
    TEST_F(OdGeMatrix3dTest, IsEqualTo)
    {
        matrix1(0, 0) = 1.000000001;
        matrix2(0, 0) = 1.0;
        EXPECT_TRUE(matrix1.isEqualTo(matrix2, 1e-6));
    }
}
