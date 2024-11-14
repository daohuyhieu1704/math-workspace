#include "pch.h"
#include "OdGePoint3d.h"

namespace Geometry
{
	const OdGePoint3d OdGePoint3d::kOrigin = OdGePoint3d();
	OdGePoint3d::OdGePoint3d()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	OdGePoint3d::OdGePoint3d(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	OdGePoint3d::~OdGePoint3d()
	{
	}

	float OdGePoint3d::DistanceTo(OdGePoint3d other) const
	{
		float dx = x - other.x;
		float dy = y - other.y;
		float dz = z - other.z;
		return sqrt(dx * dx + dy * dy + dz * dz);
	}

	OdGePoint2d OdGePoint3d::ConvertTo2d()
	{
		return OdGePoint2d(x, y);
	}

	OdGePoint3d OdGePoint3d::CenterTo(OdGePoint3d other) const
	{
		return OdGePoint3d((x + other.x) / 2, (y + other.y) / 2, (z + other.z) / 2);
	}

	void OdGePoint3d::operator+=(const OdGePoint3d& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}

	void OdGePoint3d::operator+=(const OdGeVector3d& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}

	bool OdGePoint3d::operator==(const OdGePoint3d& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	OdGePoint3d OdGePoint3d::operator*(float scalar) const
	{
		return OdGePoint3d(x * scalar, y * scalar, z * scalar);
	}

	OdGePoint3d OdGePoint3d::operator+(const OdGePoint3d& other) const
	{
		return OdGePoint3d(x + other.x, y + other.y, z + other.z);
	}

	OdGePoint3d OdGePoint3d::operator+(const OdGeVector3d& other) const
	{
		return OdGePoint3d(x + other.x, y + other.y, z + other.z);
	}

	OdGeVector3d OdGePoint3d::operator-(const OdGePoint3d& other) const
	{
		return OdGeVector3d(x - other.x, y - other.y, z - other.z);
	}

	bool OdGePoint3d::IsEqual(const OdGePoint3d& other) const
	{
		const float EPSILON = 0.00001f;
		return fabs(x - other.x) < EPSILON && fabs(y - other.y) < EPSILON && fabs(z - other.z) < EPSILON;
	}
}