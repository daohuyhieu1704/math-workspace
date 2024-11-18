#pragma once
#include <OdGePoint3d.h>
#include <OdGePoint2d.h>
#include <OdGeVector3d.h>
#include "Point2d.h"

using namespace GeometryNative;

namespace Geometry
{
    public value class Point3d
    {
    private:
        double x;
        double y;
        double z;

    public:
        Point3d(double x, double y, double z) : x(x), y(y), z(z) {}
        property double X
        {
            double get();
            void set(double value);
        }
        property double Y
        {
            double get();
            void set(double value);
        }
        property double Z
        {
            double get();
            void set(double value);
        }
        OdGePoint3d ToNative();
        static Point3d FromNative(OdGePoint3d point);

        double DistanceTo(Point3d other);
        Point2d ConvertTo2d();
        Point3d CenterTo(Point3d other);

        void operator+=(Point3d other);
        void operator+=(OdGeVector3d other);
        bool operator==(Point3d other);
        Point3d operator*(double scalar);
        Point3d operator+(Point3d other);
        Point3d operator+(OdGeVector3d other);
        OdGeVector3d operator-(Point3d other);
        bool IsEqual(Point3d other);

        static initonly Point3d Origin = Point3d(0.0, 0.0, 0.0);
    };
}
