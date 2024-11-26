#pragma once
#include "OdGePoint3d.h"
#include <optional>

namespace GeometryNative
{
	class OdGePlane
	{
	public:
		OdGePoint3d m_origin;
		OdGeVector3d m_normal;
		static const OdGePlane kXYPlane;
		static const OdGePlane kYZPlane;
		static const OdGePlane kZXPlane;
		OdGePlane();
		OdGePlane(const OdGePlane& plane);
		OdGePlane(const OdGePoint3d& origin, const OdGeVector3d& normal);
		OdGePlane(const OdGePoint3d& uPnt, const OdGePoint3d& origin, const OdGePoint3d& vPnt);
		OdGePlane(const OdGePoint3d& origin, const OdGeVector3d& uAxis, const OdGeVector3d& vAxis);
		OdGePlane(double a, double b, double c, double d);

		double DistanceTo(const OdGePoint3d& point) const;
		bool Intersect(const OdGePlane& other, OdGePoint3d& pointOnLine, OdGeVector3d& lineDirection) const;
		bool Intersect(const OdGePlane& other, OdGePoint3d& pointOnLine, OdGeVector3d& lineDirection, const double tolerance) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="rayOrigin"></param>
		/// <param name="rayDir"></param>
		/// <param name="t">Ray parameter</param>
		/// <returns></returns>
		std::optional<OdGePoint3d> intersectWith(const OdGePoint3d& rayOrigin, const OdGeVector3d& rayDir, double& t) const;
	};
}

