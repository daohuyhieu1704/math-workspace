#include "pch.h"
#include "Point2d.h"

namespace Geometry
{
    double Point2d::X::get()
    {
        return x;
    }

    void Point2d::X::set(double value)
    {
        x = value;
    }

    double Point2d::Y::get()
    {
        return y;
    }

    void Point2d::Y::set(double value)
    {
        y = value;
    }

    OdGePoint2d Point2d::ToNative()
    {
        return OdGePoint2d(x, y);
    }

    Point2d Point2d::CenterTo(Point2d point)
    {
		return Point2d((x + point.x) / 2, (y + point.y) / 2);
    }

    Point2d Point2d::FromNative(OdGePoint2d point)
    {
        return Point2d(point.x, point.y);
    }

    double Point2d::DistanceTo(Point2d point)
    {
        return ToNative().DistanceTo(point.ToNative());
    }
}
