#pragma once
#include <OdGeVector2d.h>

using namespace GeometryNative;

namespace Geometry
{
    public value class Vector2d
    {
    private:
        double x;
        double y;
    public:
        Vector2d(double x, double y) : x(x), y(y) {}

        property double X
        {
            double get();
            void set(double value);
        }

        property double Y
        {
            double get();
            void set(double value);
        }

        OdGeVector2d ToNative();
        static Vector2d FromNative(OdGeVector2d point);
        Vector2d Normalize();
        double DotProduct(Vector2d other);
        Vector2d Perpendicular();
        static Vector2d operator+(Vector2d left, Vector2d right);
        static Vector2d operator-(Vector2d left, Vector2d right);
        static Vector2d operator*(Vector2d vec, double scalar);
        static Vector2d operator*(double scalar, Vector2d vec);
        double Length();
    };
};

