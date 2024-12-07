#pragma once
#include "pch.h"
#include "OdGeVector3d.h"
#include "OdGePoint2d.h"

namespace GeometryNative
{
	class OdGeScale3d;
	class OdGeMatrix3d;
	class Quaternion3d;
	class OdGePoint3d
	{
	public:
		OdGePoint3d();
		OdGePoint3d(double x, double y, double z);
		~OdGePoint3d();

		double DistanceTo(OdGePoint3d other) const;
		OdGePoint2d ConvertTo2d();
		OdGePoint3d CenterTo(OdGePoint3d other) const;
		OdGePoint3d operator*(const OdGeMatrix3d& matrix) const;
		void operator+=(const OdGePoint3d& other);
		void operator+=(const OdGeVector3d& other);
		bool operator==(const OdGePoint3d& other) const;
		OdGePoint3d operator*(double scalar) const;
		OdGePoint3d operator*(OdGeScale3d scale) const;

		OdGePoint3d operator+(const OdGePoint3d& other) const;
		OdGePoint3d operator+(const OdGeVector3d& other) const;
		OdGeVector3d operator-(const OdGePoint3d& other) const;
		OdGePoint3d operator-(const OdGeVector3d& vec) const;
		bool isEqual(const OdGePoint3d& other) const;
		OdGeVector3d toVector3d() const;
		OdGePoint3d rotateBy(Quaternion3d quat) const;
		static const OdGePoint3d kOrigin;
		double x;
		double y;
		double z;
	};
}
