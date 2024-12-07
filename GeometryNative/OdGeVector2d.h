#pragma once
#include "pch.h"
#include "OdGePoint2d.h"

namespace GeometryNative
{
    class OdGeVector2d
    {
    public:
        OdGeVector2d();
        OdGeVector2d(double x, double y);
        ~OdGeVector2d();

        double Length() const;
        OdGeVector2d normalize() const;
        double dotProduct(const OdGeVector2d& other) const;
		OdGeVector2d perpendicular() const;

        void operator+=(const OdGeVector2d& other);
        void operator-=(const OdGeVector2d& other);
        OdGeVector2d operator+(const OdGeVector2d& other) const;
        OdGeVector2d operator-(const OdGeVector2d& other) const;
        OdGeVector2d operator*(double scalar) const;

        double x;
        double y;
    };
}
