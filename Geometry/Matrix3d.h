#pragma once
#include "Point3d.h"
#include "Vector3d.h"
#include "Scale3d.h"
#include "OdGeMatrix3d.h"

using namespace GeometryNative;

namespace Geometry
{
    public value class Matrix3d
    {
    private:
        array<double, 2>^ m_entries;

    public:
        // Constructor
        Matrix3d(array<double, 2>^ entries);

        // Static factory methods
        static Matrix3d Identity();

        // Convert to native
        OdGeMatrix3d ToNative();
        // Convert from native
        static Matrix3d FromNative(const OdGeMatrix3d& nativeMatrix);

        // Properties
        property array<double, 2>^ Entries
        {
            array<double, 2>^ get();
            void set(array<double, 2>^ value);
        }

        // Methods
        Matrix3d Multiply(Matrix3d other);
        Matrix3d& PreMultiply(Matrix3d other);
        Matrix3d& PostMultiply(Matrix3d other);
        Matrix3d Inverse();
        Matrix3d& Invert();
        Matrix3d Transpose();
        Matrix3d& TransposeIt();
        void SetToProduct(Matrix3d matrix1, Matrix3d matrix2);
        void SetToTranslation(Vector3d vect);
        Vector3d GetTranslation();
        void SetToRotation(double angle, Vector3d axis, Point3d center);
        static Matrix3d Rotation(double angle, Vector3d axis, Point3d center);
        void SetToScaling(double scale, Point3d center);
        static Matrix3d Scaling(double scale, Point3d center);
        bool IsEqualTo(Matrix3d other, double tolerance);
        double Determinant();
        double Scale();
        double Norm();
    };
}
