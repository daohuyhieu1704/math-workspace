#pragma once
#include "Point2d.h"
#include <OdGeExtents2d.h>

using namespace GeometryNative;

namespace Geometry
{
    public value class Extents2d
    {
    private:
        Point2d m_min;
        Point2d m_max;

    public:
        Extents2d(Point2d minPnt, Point2d maxPnt);
        Extents2d(double minX, double minY, double maxX, double maxY);
        OdGeExtents2d ToNative();
        static Extents2d FromNative(const OdGeExtents2d& nativeExtents);
        property Point2d MinPnt
        {
            Point2d get();
            void set(Point2d value);
        }
        property Point2d MaxPnt
        {
            Point2d get();
            void set(Point2d value);
        }
        Point2d Center();
    };
}
