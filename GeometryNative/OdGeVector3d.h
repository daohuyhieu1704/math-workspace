#pragma once
#include "pch.h"
#include "OdGeVector3d.h"
#include "OdGePoint2d.h"

namespace Geometry
{
	class OdGeVector3d
	{
	public:
		OdGeVector3d();
		OdGeVector3d(float x, float y, float z);
		~OdGeVector3d();

		float Length() const;
		OdGeVector3d Normalize() const;
		OdGeVector3d CrossProduct(const OdGeVector3d& other) const;
		float DotProduct(const OdGeVector3d& other) const;

		OdGeVector3d operator-() const;
		void operator+=(const OdGeVector3d& other);
		void operator-=(const OdGeVector3d& other);
		OdGeVector3d operator+(const OdGeVector3d& other) const;
		OdGeVector3d operator-(const OdGeVector3d& other) const;
		OdGeVector3d operator*(float scalar) const;
		OdGeVector3d operator/=(const float scale);

		bool IsEqual(const OdGeVector3d& other) const;

		float x;
		float y;
		float z;
	};
}

