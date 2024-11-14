#pragma once
#include "pch.h"
#include "OdGeVector3d.h"
#include "OdGePoint2d.h"

namespace GeometryNative
{
	class OdGePoint3d
	{
	public:
		OdGePoint3d();
		OdGePoint3d(double x, double y, double z);
		~OdGePoint3d();

		double DistanceTo(OdGePoint3d other) const;
		OdGePoint2d ConvertTo2d();
		OdGePoint3d CenterTo(OdGePoint3d other) const;

		void operator+=(const OdGePoint3d& other);
		void operator+=(const OdGeVector3d& other);
		bool operator==(const OdGePoint3d& other) const;
		OdGePoint3d operator*(double scalar) const;

		OdGePoint3d operator+(const OdGePoint3d& other) const;
		OdGePoint3d operator+(const OdGeVector3d& other) const;
		OdGeVector3d operator-(const OdGePoint3d& other) const;
		bool IsEqual(const OdGePoint3d& other) const;
		static const OdGePoint3d kOrigin;
		double x;
		double y;
		double z;
	};
}
