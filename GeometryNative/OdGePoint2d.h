#pragma once

namespace GeometryNative
{
	class OdGePoint2d
	{
	public:
		static const OdGePoint2d kOrigin;
		OdGePoint2d();
		OdGePoint2d(double x, double y);
		~OdGePoint2d();
		double DistanceTo(OdGePoint2d point) const;
		double x;
		double y;
	};
}
