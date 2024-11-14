#pragma once

namespace Geometry
{
	class OdGePoint2d
	{
	public:
		static const OdGePoint2d kOrigin;
		OdGePoint2d();
		OdGePoint2d(float x, float y);
		~OdGePoint2d();
		double DistanceTo(OdGePoint2d point) const;
		float x;
		float y;
	};
}
