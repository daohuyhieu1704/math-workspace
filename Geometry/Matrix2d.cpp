#include "pch.h"
#include "Matrix2d.h"

namespace Geometry
{
    Matrix2d::Matrix2d(array<double, 2>^ entries)
    {
        if (entries->GetLength(0) != 3 || entries->GetLength(1) != 3)
        {
            throw gcnew System::ArgumentException("Matrix must be 3x3.");
        }
        m_entries = entries;
    }

    Matrix2d Matrix2d::Identity()
    {
        array<double, 2>^ identity = gcnew array<double, 2>(3, 3);
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                identity[i, j] = (i == j) ? 1.0 : 0.0;
            }
        }
        return Matrix2d(identity);
    }

    OdGeMatrix2d Matrix2d::ToNative()
    {
        OdGeMatrix2d nativeMatrix;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                nativeMatrix(i, j) = m_entries[i, j];
            }
        }
        return nativeMatrix;
    }

    Matrix2d Matrix2d::FromNative(const OdGeMatrix2d& nativeMatrix)
    {
        array<double, 2>^ entries = gcnew array<double, 2>(3, 3);
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                entries[i, j] = nativeMatrix(i, j);
            }
        }
        return Matrix2d(entries);
    }

    array<double, 2>^ Matrix2d::Entries::get()
    {
        return m_entries;
    }

    void Matrix2d::Entries::set(array<double, 2>^ value)
    {
        if (value->GetLength(0) != 3 || value->GetLength(1) != 3)
        {
            throw gcnew System::ArgumentException("Matrix must be 3x3.");
        }
        m_entries = value;
    }

    Matrix2d Matrix2d::Multiply(Matrix2d other)
    {
        OdGeMatrix2d result = ToNative() * other.ToNative();
        return FromNative(result);
    }

    Matrix2d& Matrix2d::PreMultiply(Matrix2d other)
    {
        Matrix2d ret = FromNative(other.ToNative() * ToNative());
        return ret;
    }

    Matrix2d& Matrix2d::PostMultiply(Matrix2d other)
    {
        Matrix2d ret = FromNative(ToNative() * other.ToNative());
        return ret;
    }

    Matrix2d Matrix2d::Inverse()
    {
        OdGeMatrix2d result = ToNative().inverse();
        return FromNative(result);
    }

    Matrix2d& Matrix2d::Invert()
    {
		Matrix2d ret = FromNative(ToNative().invert());
		return ret;
    }

    Matrix2d Matrix2d::Transpose()
    {
        OdGeMatrix2d result = ToNative().transpose();
        return FromNative(result);
    }

    Matrix2d& Matrix2d::TransposeIt()
    {
        Matrix2d ret = FromNative(ToNative().transposeIt());
        return ret;
    }

    void Matrix2d::SetToProduct(Matrix2d matrix1, Matrix2d matrix2)
    {
        OdGeMatrix2d result;
        result.setToProduct(matrix1.ToNative(), matrix2.ToNative());
        *this = FromNative(result);
    }

    void Matrix2d::SetToTranslation(Vector2d vect)
    {
        OdGeMatrix2d native = ToNative();
        native.setToTranslation(vect.ToNative());
        *this = FromNative(native);
    }

    Vector2d Matrix2d::GetTranslation()
    {
        return Vector2d::FromNative(ToNative().translation());
    }

    void Matrix2d::SetToRotation(double angle, Point2d center)
    {
        OdGeMatrix2d native = ToNative();
        native.setToRotation(angle, center.ToNative());
        *this = FromNative(native);
    }

    Matrix2d Matrix2d::Rotation(double angle, Point2d center)
    {
        return FromNative(OdGeMatrix2d::rotation(angle, center.ToNative()));
    }

    void Matrix2d::SetToScaling(double scale, Point2d center)
    {
        OdGeMatrix2d native = ToNative();
        native.setToScaling(scale, center.ToNative());
        *this = FromNative(native);
    }

    Matrix2d Matrix2d::Scaling(double scale, Point2d center)
    {
        return FromNative(OdGeMatrix2d::scaling(scale, center.ToNative()));
    }

    bool Matrix2d::IsEqualTo(Matrix2d other, double tolerance)
    {
        return ToNative().isEqualTo(other.ToNative(), tolerance);
    }

    double Matrix2d::Determinant()
    {
        return ToNative().det();
    }
}
