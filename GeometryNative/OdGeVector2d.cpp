#include "pch.h"
#include "OdGeVector2d.h"

namespace Geometry
{
    OdGeVector2d::OdGeVector2d() : x(0), y(0) {}
    OdGeVector2d::OdGeVector2d(float x, float y) : x(x), y(y) {}
    OdGeVector2d::~OdGeVector2d() {}

    float OdGeVector2d::Length() const
    {
        return sqrt(x * x + y * y);
    }

    OdGeVector2d OdGeVector2d::Normalize() const
    {
        float length = Length();
        return OdGeVector2d(x / length, y / length);
    }

    float OdGeVector2d::DotProduct(const OdGeVector2d& other) const
    {
        return x * other.x + y * other.y;
    }

    void OdGeVector2d::operator+=(const OdGeVector2d& other)
    {
        x += other.x;
        y += other.y;
    }

    void OdGeVector2d::operator-=(const OdGeVector2d& other)
    {
        x -= other.x;
        y -= other.y;
    }

    OdGeVector2d OdGeVector2d::operator+(const OdGeVector2d& other) const
    {
        return OdGeVector2d(x + other.x, y + other.y);
    }

    OdGeVector2d OdGeVector2d::operator-(const OdGeVector2d& other) const
    {
        return OdGeVector2d(x - other.x, y - other.y);
    }

    OdGeVector2d OdGeVector2d::operator*(float scalar) const
    {
        return OdGeVector2d(x * scalar, y * scalar);
    }
}
