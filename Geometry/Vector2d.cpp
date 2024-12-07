#include "pch.h"
#include "Vector2d.h"

namespace Geometry
{
    double Vector2d::X::get()
    {
        return x;
    }

    void Vector2d::X::set(double value)
    {
        x = value;
    }

    double Vector2d::Y::get()
    {
        return y;
    }

    void Vector2d::Y::set(double value)
    {
        y = value;
    }

    OdGeVector2d Vector2d::ToNative()
    {
        return OdGeVector2d(x, y);
    }

    Vector2d Vector2d::FromNative(OdGeVector2d point)
    {
        return Vector2d(point.x, point.y);
    }
    Vector2d Vector2d::Normalize()
    {
        OdGeVector2d nativeVec = ToNative().normalize();
        return FromNative(nativeVec);
    }
    double Vector2d::DotProduct(Vector2d other)
    {
        OdGeVector2d nativeVec = this->ToNative();
        OdGeVector2d otherNative = other.ToNative();
        return nativeVec.dotProduct(otherNative);
    }
    Vector2d Vector2d::Perpendicular()
    {
        OdGeVector2d nativeVec = this->ToNative().perpendicular();
        return FromNative(nativeVec);
    }
    Vector2d Vector2d::operator+(Vector2d left, Vector2d right)
    {
        OdGeVector2d result = left.ToNative() + right.ToNative();
        return FromNative(result);
    }
    Vector2d Vector2d::operator-(Vector2d left, Vector2d right)
    {
        OdGeVector2d result = left.ToNative() - right.ToNative();
        return FromNative(result);
    }
    Vector2d Vector2d::operator*(Vector2d vec, double scalar)
    {
        OdGeVector2d result = vec.ToNative() * scalar;
        return FromNative(result);
    }
    Vector2d Vector2d::operator*(double scalar, Vector2d vec)
    {
        return vec * scalar;
    }
    double Vector2d::Length()
    {
        return ToNative().Length();
    }
}
