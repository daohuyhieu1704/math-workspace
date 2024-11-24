#pragma once
#include <OdGeVector3d.h>

using namespace GeometryNative;

namespace Geometry
{
    public value class Vector3d
    {
    private:
        double x;
        double y;
        double z;

    public:
        Vector3d(double x, double y, double z) : x(x), y(y), z(z) {}
        property double X
        {
            double get() { return x; }
            void set(double value) { x = value; }
        }

        property double Y
        {
            double get() { return y; }
            void set(double value) { y = value; }
        }

        property double Z
        {
            double get() { return z; }
            void set(double value) { z = value; }
        }
        OdGeVector3d ToNative();
        static Vector3d FromNative(OdGeVector3d nativeVec);
        double Length();
        Vector3d Normalize();
        Vector3d Perpendicular();
        Vector3d CrossProduct(Vector3d other);
        double DotProduct(Vector3d other);
        static Vector3d operator+(Vector3d left, Vector3d right);
        static Vector3d operator-(Vector3d left, Vector3d right);
        static Vector3d operator*(Vector3d vec, double scalar);
        static Vector3d operator*(double scalar, Vector3d vec);
        static Vector3d operator/(Vector3d vec, double scalar);
        static Vector3d operator-(Vector3d vec);
        bool IsEqual(Vector3d other);
        bool IsParallelTo(Vector3d other);
        static initonly Vector3d XAxis = FromNative(OdGeVector3d::kXAxis);
        static initonly Vector3d YAxis = FromNative(OdGeVector3d::kYAxis);
        static initonly Vector3d ZAxis = FromNative(OdGeVector3d::kZAxis);
    };
}