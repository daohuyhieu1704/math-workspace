#pragma once
#include "pch.h"
#include "OdGePoint2d.h"

namespace Geometry
{
    class OdGeVector2d
    {
    public:
        OdGeVector2d();
        OdGeVector2d(float x, float y);
        ~OdGeVector2d();

        float Length() const;
        OdGeVector2d Normalize() const;
        float DotProduct(const OdGeVector2d& other) const;

        void operator+=(const OdGeVector2d& other);
        void operator-=(const OdGeVector2d& other);
        OdGeVector2d operator+(const OdGeVector2d& other) const;
        OdGeVector2d operator-(const OdGeVector2d& other) const;
        OdGeVector2d operator*(float scalar) const;

        float x;
        float y;
    };
}
