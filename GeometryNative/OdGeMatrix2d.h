#pragma once
#include "OdGePoint2d.h"
#include "OdGeVector2d.h"
#include <algorithm>

namespace GeometryNative
{
    class OdGeMatrix2d
    {
    public:
        OdGeMatrix2d()
        {
            setToIdentity();
        }

        OdGeMatrix2d& setToIdentity()
        {
            entry[0][0] = 1.0; entry[0][1] = 0.0; entry[0][2] = 0.0;
            entry[1][0] = 0.0; entry[1][1] = 1.0; entry[1][2] = 0.0;
            entry[2][0] = 0.0; entry[2][1] = 0.0; entry[2][2] = 1.0;
            return *this;
        }

        OdGeMatrix2d operator* (const OdGeMatrix2d& matrix) const
        {
            OdGeMatrix2d result;
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    result.entry[i][j] = 0.0;
                    for (int k = 0; k < 3; ++k)
                    {
                        result.entry[i][j] += entry[i][k] * matrix.entry[k][j];
                    }
                }
            }
            return result;
        }

        OdGeMatrix2d& operator*= (const OdGeMatrix2d& matrix)
        {
            *this = *this * matrix;
            return *this;
        }

        OdGeMatrix2d& preMultBy(const OdGeMatrix2d& leftSide)
        {
            *this = leftSide * (*this);
            return *this;
        }

        OdGeMatrix2d& postMultBy(const OdGeMatrix2d& rightSide)
        {
            *this = *this * rightSide;
            return *this;
        }

        OdGeMatrix2d& setToProduct(const OdGeMatrix2d& matrix1, const OdGeMatrix2d& matrix2)
        {
            *this = matrix1 * matrix2;
            return *this;
        }

        OdGeMatrix2d& invert()
        {
            double determinant = det();
            if (std::abs(determinant) < 1e-9) // Check if determinant is nearly zero
            {
                setToIdentity(); // Cannot invert, return identity
                return *this;
            }

            double invDet = 1.0 / determinant;
            OdGeMatrix2d temp = *this;

            entry[0][0] = temp.entry[1][1] * invDet;
            entry[0][1] = -temp.entry[0][1] * invDet;
            entry[1][0] = -temp.entry[1][0] * invDet;
            entry[1][1] = temp.entry[0][0] * invDet;
            entry[0][2] = -(temp.entry[0][2] * entry[0][0] + temp.entry[1][2] * entry[0][1]);
            entry[1][2] = -(temp.entry[0][2] * entry[1][0] + temp.entry[1][2] * entry[1][1]);
            entry[2][0] = entry[2][1] = 0.0;
            entry[2][2] = 1.0;

            return *this;
        }

        OdGeMatrix2d inverse() const
        {
            OdGeMatrix2d result = *this;
            return result.invert();
        }

        OdGeMatrix2d& transposeIt()
        {
            std::swap(entry[0][1], entry[1][0]);
            return *this;
        }

        OdGeMatrix2d transpose() const
        {
            OdGeMatrix2d result = *this;
            return result.transposeIt();
        }

        bool operator ==(const OdGeMatrix2d& matrix) const
        {
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    if (entry[i][j] != matrix.entry[i][j])
                        return false;
                }
            }
            return true;
        }

        bool operator !=(const OdGeMatrix2d& matrix) const
        {
            return !(*this == matrix);
        }

        bool isEqualTo(const OdGeMatrix2d& matrix, double tol = 1e-9) const
        {
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    if (std::abs(entry[i][j] - matrix.entry[i][j]) > tol)
                        return false;
                }
            }
            return true;
        }

        double det() const
        {
            return entry[0][0] * entry[1][1] - entry[0][1] * entry[1][0];
        }

        OdGeMatrix2d& setTranslation(const OdGeVector2d& vect)
        {
            entry[0][2] = vect.x;
            entry[1][2] = vect.y;
            return *this;
        }

        OdGeVector2d translation() const
        {
            return OdGeVector2d(entry[0][2], entry[1][2]);
        }

        static OdGeMatrix2d translation(const OdGeVector2d& vector)
        {
            OdGeMatrix2d result;
            result.setTranslation(vector);
            return result;
        }

        OdGeMatrix2d& setToTranslation(const OdGeVector2d& vect)
        {
            setToIdentity();
            setTranslation(vect);
            return *this;
        }

        OdGeMatrix2d& setToRotation(double angle, const OdGePoint2d& center = OdGePoint2d::kOrigin)
        {
            setToIdentity();
            double cosA = cos(angle);
            double sinA = sin(angle);

            entry[0][0] = cosA;
            entry[0][1] = -sinA;
            entry[1][0] = sinA;
            entry[1][1] = cosA;

            setTranslation(OdGeVector2d(center.x - cosA * center.x + sinA * center.y,
                center.y - sinA * center.x - cosA * center.y));
            return *this;
        }

        static OdGeMatrix2d rotation(double angle, const OdGePoint2d& center = OdGePoint2d::kOrigin)
        {
            OdGeMatrix2d result;
            result.setToRotation(angle, center);
            return result;
        }

        OdGeMatrix2d& setToScaling(double scale, const OdGePoint2d& center = OdGePoint2d::kOrigin)
        {
            setToIdentity();
            entry[0][0] = scale;
            entry[1][1] = scale;
            setTranslation(OdGeVector2d(center.x * (1 - scale), center.y * (1 - scale)));
            return *this;
        }

        static OdGeMatrix2d scaling(double scale, const OdGePoint2d& center = OdGePoint2d::kOrigin)
        {
            OdGeMatrix2d result;
            result.setToScaling(scale, center);
            return result;
        }

        const double* operator [](int row) const
        {
            return entry[row];
        }

        double* operator [](int row)
        {
            return entry[row];
        }

        double operator ()(int row, int column) const
        {
            return entry[row][column];
        }

        double& operator ()(int row, int column)
        {
            return entry[row][column];
        }

        double entry[3][3];
    };
}
