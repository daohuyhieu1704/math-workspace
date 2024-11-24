#pragma once
#include "Point3d.h"
#include "Vector3d.h"
#include "OdGePlane.h"

using namespace GeometryNative;

namespace Geometry
{
    public value class Plane
    {
    private:
        Point3d m_origin;
        Vector3d m_normal;

    public:
        Plane(Point3d origin, Vector3d normal);
        Plane(Point3d uPnt, Point3d origin, Point3d vPnt);
        Plane(Vector3d uAxis, Vector3d vAxis, Point3d origin);
        Plane(double a, double b, double c, double d);
        static Plane XYPlane();
        static Plane YZPlane();
        static Plane ZXPlane();
        OdGePlane ToNative();
        static Plane FromNative(const OdGePlane& nativePlane);
        property Point3d Origin
        {
            Point3d get();
            void set(Point3d value);
        }

        property Vector3d Normal
        {
            Vector3d get();
            void set(Vector3d value);
        }
        double DistanceTo(Point3d point);
        bool Intersect(Plane other, [System::Runtime::InteropServices::Out] Point3d% pointOnLine, [System::Runtime::InteropServices::Out] Vector3d% lineDirection, double tolerance);
    };
}
