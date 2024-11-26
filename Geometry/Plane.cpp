#include "pch.h"
#include "Plane.h"

namespace Geometry
{
    Plane::Plane(Point3d origin, Vector3d normal)
        : m_origin(origin), m_normal(normal) {
    }

    Plane::Plane(Point3d uPnt, Point3d origin, Point3d vPnt)
    {
        OdGePlane nativePlane(origin.ToNative(), uPnt.ToNative(), vPnt.ToNative());
        *this = FromNative(nativePlane);
    }

    Plane::Plane(Vector3d uAxis, Vector3d vAxis, Point3d origin)
    {
        OdGePlane nativePlane(origin.ToNative(), uAxis.ToNative(), vAxis.ToNative());
        *this = FromNative(nativePlane);
    }

    Plane::Plane(double a, double b, double c, double d)
    {
        OdGePlane nativePlane(a, b, c, d);
        *this = FromNative(nativePlane);
    }

    Plane Plane::XYPlane()
    {
        return FromNative(OdGePlane::kXYPlane);
    }

    Plane Plane::YZPlane()
    {
        return FromNative(OdGePlane::kYZPlane);
    }

    Plane Plane::ZXPlane()
    {
        return FromNative(OdGePlane::kZXPlane);
    }

    OdGePlane Plane::ToNative()
    {
        return OdGePlane(m_origin.ToNative(), m_normal.ToNative());
    }

    Plane Plane::FromNative(const OdGePlane& nativePlane)
    {
        return Plane(
            Point3d::FromNative(nativePlane.m_origin),
            Vector3d::FromNative(nativePlane.m_normal));
    }

    Point3d Plane::Origin::get()
    {
        return m_origin;
    }

    void Plane::Origin::set(Point3d value)
    {
        m_origin = value;
    }

    Vector3d Plane::Normal::get()
    {
        return m_normal;
    }

    void Plane::Normal::set(Vector3d value)
    {
        m_normal = value;
    }

    double Plane::DistanceTo(Point3d point)
    {
        OdGePlane native = ToNative();
        return native.DistanceTo(point.ToNative());
    }

    bool Plane::Intersect(Plane other, [System::Runtime::InteropServices::Out] Point3d% pointOnLine, [System::Runtime::InteropServices::Out] Vector3d% lineDirection, double tolerance)
    {
        OdGePoint3d nativePointOnLine;
        OdGeVector3d nativeLineDirection;

        bool intersects = ToNative().Intersect(other.ToNative(), nativePointOnLine, nativeLineDirection, tolerance);

        if (intersects)
        {
            pointOnLine = Point3d::FromNative(nativePointOnLine);
            lineDirection = Vector3d::FromNative(nativeLineDirection);
        }

        return intersects;
    }
}
