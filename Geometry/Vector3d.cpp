#include "pch.h"
#include "Vector3d.h"

namespace Geometry
{
    OdGeVector3d Vector3d::ToNative()
    {
        return OdGeVector3d(x, y, z);
    }
    Vector3d Vector3d::FromNative(OdGeVector3d nativeVec)
    {
        return Vector3d(nativeVec.x, nativeVec.y, nativeVec.z);
    }
    double Vector3d::Length()
    {
		return ToNative().Length();
    }
    Vector3d Vector3d::Normalize()
    {
        return FromNative(ToNative().normalize());
    }
    Vector3d Vector3d::Perpendicular()
    {
        return FromNative(ToNative().perpendicular());
    }
    Vector3d Vector3d::CrossProduct(Vector3d other)
    {
        return FromNative(ToNative().crossProduct(other.ToNative()));
    }
    double Vector3d::DotProduct(Vector3d other)
    {
        return ToNative().dotProduct(other.ToNative());
    }
    Vector3d Vector3d::operator+(Vector3d left, Vector3d right)
    {
        return FromNative(left.ToNative() + right.ToNative());
    }
    Vector3d Vector3d::operator-(Vector3d left, Vector3d right)
    {
        return FromNative(left.ToNative() - right.ToNative());
    }
    Vector3d Vector3d::operator*(Vector3d vec, double scalar)
    {
        return FromNative(vec.ToNative() * scalar);
    }
    Vector3d Vector3d::operator*(double scalar, Vector3d vec)
    {
        return vec * scalar;
    }
    Vector3d Vector3d::operator/(Vector3d vec, double scalar)
    {
        return FromNative(vec.ToNative() / scalar);
    }
    Vector3d Vector3d::operator-(Vector3d vec)
    {
        return FromNative(-vec.ToNative());
    }
    bool Vector3d::IsEqual(Vector3d other)
    {
        return ToNative().isEqual(other.ToNative());
    }
    bool Vector3d::IsParallelTo(Vector3d other)
    {
        return ToNative().isParallelTo(other.ToNative());
    }
}
