#pragma once
#include <OdGePoint2d.h>

using namespace GeometryNative;

namespace Geometry
{
	public value class Point2d
	{
    private:
        double x;
        double y;
    public:
        Point2d(double x, double y) : x(x), y(y) {}

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

        OdGePoint2d ToNative();
        static Point2d FromNative(OdGePoint2d point);
        double DistanceTo(Point2d point);
    };
};
