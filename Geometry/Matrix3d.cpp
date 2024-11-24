#include "pch.h"
#include "Matrix3d.h"

namespace Geometry
{
    Matrix3d::Matrix3d(array<double, 2>^ entries)
    {
        if (entries->GetLength(0) != 4 || entries->GetLength(1) != 4)
        {
            throw gcnew System::ArgumentException("Matrix must be 4x4.");
        }
        m_entries = entries;
    }

    Matrix3d Matrix3d::Identity()
    {
        array<double, 2>^ identity = gcnew array<double, 2>(4, 4);
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                identity[i, j] = (i == j) ? 1.0 : 0.0;
            }
        }
        return Matrix3d(identity);
    }

    OdGeMatrix3d Matrix3d::ToNative()
    {
        OdGeMatrix3d nativeMatrix;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                nativeMatrix(i, j) = m_entries[i, j];
            }
        }
        return nativeMatrix;
    }

    Matrix3d Matrix3d::FromNative(const OdGeMatrix3d& nativeMatrix)
    {
        array<double, 2>^ entries = gcnew array<double, 2>(4, 4);
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                entries[i, j] = nativeMatrix(i, j);
            }
        }
        return Matrix3d(entries);
    }

    array<double, 2>^ Matrix3d::Entries::get()
    {
        return m_entries;
    }

    void Matrix3d::Entries::set(array<double, 2>^ value)
    {
        if (value->GetLength(0) != 4 || value->GetLength(1) != 4)
        {
            throw gcnew System::ArgumentException("Matrix must be 4x4.");
        }
        m_entries = value;
    }

    Matrix3d Matrix3d::Multiply(Matrix3d other)
    {
        OdGeMatrix3d result = ToNative() * other.ToNative();
        return FromNative(result);
    }

    Matrix3d& Matrix3d::PreMultiply(Matrix3d other)
    {
        Matrix3d retVal = FromNative(other.ToNative() * ToNative());
        return retVal;
    }

    Matrix3d& Matrix3d::PostMultiply(Matrix3d other)
    {
        Matrix3d retVal = FromNative(ToNative() * other.ToNative());
        return retVal;
    }

    Matrix3d Matrix3d::Inverse()
    {
        OdGeMatrix3d result = ToNative().inverse();
        return FromNative(result);
    }

    Matrix3d& Matrix3d::Invert()
    {
        Matrix3d retVal = FromNative(ToNative().invert());
        return retVal;
    }

    Matrix3d Matrix3d::Transpose()
    {
        OdGeMatrix3d result = ToNative().transpose();
        return FromNative(result);
    }

    Matrix3d& Matrix3d::TransposeIt()
    {
        Matrix3d retVal = FromNative(ToNative().transposeIt());
        return retVal;
    }

    void Matrix3d::SetToProduct(Matrix3d matrix1, Matrix3d matrix2)
    {
        OdGeMatrix3d result;
        result.setToProduct(matrix1.ToNative(), matrix2.ToNative());
        *this = FromNative(result);
    }

    void Matrix3d::SetToTranslation(Vector3d vect)
    {
        OdGeMatrix3d native = ToNative();
        native.setToTranslation(vect.ToNative());
        *this = FromNative(native);
    }

    Vector3d Matrix3d::GetTranslation()
    {
        OdGeVector3d vect;
        ToNative().translation(vect);
        return Vector3d::FromNative(vect);
    }

    void Matrix3d::SetToRotation(double angle, Vector3d axis, Point3d center)
    {
        OdGeMatrix3d native = ToNative();
        native.setToRotation(angle, axis.ToNative(), center.ToNative());
        *this = FromNative(native);
    }

    Matrix3d Matrix3d::Rotation(double angle, Vector3d axis, Point3d center)
    {
        return FromNative(OdGeMatrix3d::rotation(angle, axis.ToNative(), center.ToNative()));
    }

    void Matrix3d::SetToScaling(double scale, Point3d center)
    {
        OdGeMatrix3d native = ToNative();
        native.setToScaling(scale, center.ToNative());
        *this = FromNative(native);
    }

    Matrix3d Matrix3d::Scaling(double scale, Point3d center)
    {
        return FromNative(OdGeMatrix3d::scaling(scale, center.ToNative()));
    }

    bool Matrix3d::IsEqualTo(Matrix3d other, double tolerance)
    {
        return ToNative().isEqualTo(other.ToNative(), tolerance);
    }

    double Matrix3d::Determinant()
    {
        return ToNative().det();
    }

    double Matrix3d::Scale()
    {
        return ToNative().scale();
    }

    double Matrix3d::Norm()
    {
        return ToNative().norm();
    }
}
