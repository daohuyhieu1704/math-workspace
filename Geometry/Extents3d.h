#pragma once
#include <OdGeExtents3d.h>
#include "Point3d.h"

using namespace GeometryNative;

namespace Geometry
{
    public value class Extents3d
    {
    private:
        Point3d m_min;
        Point3d m_max;

    public:
        Extents3d(Point3d minPnt, Point3d maxPnt);
        Extents3d(double minX, double minY, double minZ, double maxX, double maxY, double maxZ);
        OdGeExtents3d ToNative();
        static Extents3d FromNative(const OdGeExtents3d& nativeExtents);
        property Point3d MinPnt
        {
            Point3d get();
            void set(Point3d value);
        }
        property Point3d MaxPnt
        {
            Point3d get();
            void set(Point3d value);
        }
        void Set(Point3d min, Point3d max);
        void AddPoint(Point3d point);
        bool IsValidExtents();
        void ExpandBy(double dx, double dy, double dz);
        Point3d Center();
    };
}
