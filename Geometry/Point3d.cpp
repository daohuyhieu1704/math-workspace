#include "pch.h"
#include "Point3d.h"
#include "Point2d.h"

namespace Geometry
{
    // Property Implementations
    double Point3d::X::get() { return x; }
    void Point3d::X::set(double value) { x = value; }
    double Point3d::Y::get() { return y; }
    void Point3d::Y::set(double value) { y = value; }
    double Point3d::Z::get() { return z; }
    void Point3d::Z::set(double value) { z = value; }

    // Conversion Methods
    OdGePoint3d Point3d::ToNative()
    {
        return OdGePoint3d(x, y, z);
    }

    Point3d Point3d::FromNative(OdGePoint3d point)
    {
        return Point3d(point.x, point.y, point.z);
    }

    // Functions
    double Point3d::DistanceTo(Point3d other)
    {
        return ToNative().DistanceTo(other.ToNative());
    }

    Point2d Point3d::ConvertTo2d()
    {
        OdGePoint2d native2d = ToNative().ConvertTo2d();
        return Point2d::FromNative(native2d);
    }

    Point3d Point3d::CenterTo(Point3d other)
    {
        OdGePoint3d result = ToNative().CenterTo(other.ToNative());
        return FromNative(result);
    }

    // Operator Overloads
    void Point3d::operator+=(Point3d other)
    {
        OdGePoint3d nativeResult = ToNative();
        nativeResult += other.ToNative();
        *this = FromNative(nativeResult);
    }

    void Point3d::operator+=(OdGeVector3d other)
    {
        OdGePoint3d nativeResult = ToNative();
        nativeResult += other;
        *this = FromNative(nativeResult);
    }

    bool Point3d::operator==(Point3d other)
    {
        return ToNative() == other.ToNative();
    }

    Point3d Point3d::operator*(double scalar)
    {
        OdGePoint3d result = ToNative() * scalar;
        return FromNative(result);
    }

    Point3d Point3d::operator+(Point3d other)
    {
        OdGePoint3d result = ToNative() + other.ToNative();
        return FromNative(result);
    }

    Point3d Point3d::operator+(OdGeVector3d other)
    {
        OdGePoint3d result = ToNative() + other;
        return FromNative(result);
    }

    OdGeVector3d Point3d::operator-(Point3d other)
    {
        return ToNative() - other.ToNative();
    }

    bool Point3d::IsEqual(Point3d other)
    {
        return ToNative().isEqual(other.ToNative());
    }
    System::String^ Point3d::ToString()
    {
		return System::String::Format("({0}, {1}, {2})", x, y, z);
    }
}
