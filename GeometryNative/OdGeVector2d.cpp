#include "pch.h"
#include "OdGeVector2d.h"

namespace GeometryNative
{
    OdGeVector2d::OdGeVector2d() : x(0), y(0) {}
    OdGeVector2d::OdGeVector2d(double x, double y) : x(x), y(y) {}
    OdGeVector2d::~OdGeVector2d() {}

    double OdGeVector2d::Length() const
    {
        return sqrt(x * x + y * y);
    }

    OdGeVector2d OdGeVector2d::Normalize() const
    {
        double length = Length();
        return OdGeVector2d(x / length, y / length);
    }

    double OdGeVector2d::DotProduct(const OdGeVector2d& other) const
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

    OdGeVector2d OdGeVector2d::operator*(double scalar) const
    {
        return OdGeVector2d(x * scalar, y * scalar);
    }
}
