#include "pch.h"
#include "Extents3d.h"

namespace Geometry
{
    Extents3d::Extents3d(Point3d minPnt, Point3d maxPnt)
        : m_min(minPnt), m_max(maxPnt) {
    }

    Extents3d::Extents3d(double minX, double minY, double minZ, double maxX, double maxY, double maxZ)
        : m_min(Point3d(minX, minY, minZ)), m_max(Point3d(maxX, maxY, maxZ)) {
    }

    OdGeExtents3d Extents3d::ToNative()
    {
        return OdGeExtents3d(m_min.ToNative(), m_max.ToNative());
    }

    Extents3d Extents3d::FromNative(const OdGeExtents3d& nativeExtents)
    {
        return Extents3d(
            Point3d::FromNative(nativeExtents.GetMinPnt()),
            Point3d::FromNative(nativeExtents.GetMaxPnt()));
    }

    Point3d Extents3d::MinPnt::get()
    {
        return m_min;
    }

    void Extents3d::MinPnt::set(Point3d value)
    {
        m_min = value;
    }

    Point3d Extents3d::MaxPnt::get()
    {
        return m_max;
    }

    void Extents3d::MaxPnt::set(Point3d value)
    {
        m_max = value;
    }

    void Extents3d::Set(Point3d min, Point3d max)
    {
        m_min = min;
        m_max = max;
    }

    void Extents3d::AddPoint(Point3d point)
    {
        OdGeExtents3d native = ToNative();
        native.appendPoint_s(point.ToNative());
        *this = FromNative(native);
    }

    bool Extents3d::IsValidExtents()
    {
        return ToNative().isValidExtents();
    }

    void Extents3d::ExpandBy(double dx, double dy, double dz)
    {
        OdGeVector3d vect(dx, dy, dz);
        OdGeExtents3d native = ToNative();
        native.expandBy(vect);
        *this = FromNative(native);
    }

    Point3d Extents3d::Center()
    {
        return Point3d::FromNative(ToNative().getCenter());
    }
}
