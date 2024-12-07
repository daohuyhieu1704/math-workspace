#pragma once
#include "Point2d.h"
#include "Vector2d.h"
#include "OdGeMatrix2d.h"

using namespace GeometryNative;

namespace Geometry
{
    public value class Matrix2d
    {
    private:
        array<double, 2>^ m_entries;

    public:
        Matrix2d(array<double, 2>^ entries);
        OdGeMatrix2d ToNative();
        static Matrix2d FromNative(const OdGeMatrix2d& nativeMatrix);
        property array<double, 2>^ Entries
        {
            array<double, 2>^ get();
            void set(array<double, 2>^ value);
        }
        Matrix2d Identity();
        Matrix2d Multiply(Matrix2d other);
        Matrix2d& PreMultiply(Matrix2d other);
        Matrix2d& PostMultiply(Matrix2d other);
        Matrix2d Inverse();
        Matrix2d& Invert();
        Matrix2d Transpose();
        Matrix2d& TransposeIt();
        void SetToProduct(Matrix2d matrix1, Matrix2d matrix2);
        void SetToTranslation(Vector2d vect);
        Vector2d GetTranslation();
        void SetToRotation(double angle, Point2d center);
        static Matrix2d Rotation(double angle, Point2d center);
        void SetToScaling(double scale, Point2d center);
        static Matrix2d Scaling(double scale, Point2d center);
        bool IsEqualTo(Matrix2d other, double tolerance);
        double Determinant();
    };
}