#include "pch.h"
#include "Extents2d.h"

namespace Geometry
{
    Extents2d::Extents2d(Point2d minPnt, Point2d maxPnt)
        : m_min(minPnt), m_max(maxPnt) {
    }

    Extents2d::Extents2d(double minX, double minY, double maxX, double maxY)
        : m_min(Point2d(minX, minY)), m_max(Point2d(maxX, maxY)) {
    }

    OdGeExtents2d Extents2d::ToNative()
    {
        return OdGeExtents2d(m_min.ToNative(), m_max.ToNative());
    }

    Extents2d Extents2d::FromNative(const OdGeExtents2d& nativeExtents)
    {
        return Extents2d(
            Point2d::FromNative(nativeExtents.GetMinPnt()),
            Point2d::FromNative(nativeExtents.GetMaxPnt()));
    }

    Point2d Extents2d::MinPnt::get()
    {
        return m_min;
    }

    void Extents2d::MinPnt::set(Point2d value)
    {
        m_min = value;
    }

    Point2d Extents2d::MaxPnt::get()
    {
        return m_max;
    }

    void Extents2d::MaxPnt::set(Point2d value)
    {
        m_max = value;
    }

    Point2d Extents2d::Center()
    {
        return Point2d(
            (m_min.X + m_max.X) / 2.0,
            (m_min.Y + m_max.Y) / 2.0);
    }
}
