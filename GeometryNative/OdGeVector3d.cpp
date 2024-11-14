#include "pch.h"
#include "OdGeVector3d.h"
#include <cfloat>

namespace Geometry
{
	OdGeVector3d::OdGeVector3d()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	OdGeVector3d::OdGeVector3d(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	OdGeVector3d::~OdGeVector3d()
	{
	}

	float OdGeVector3d::Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	OdGeVector3d OdGeVector3d::Normalize() const
	{
		float length = Length();
		return OdGeVector3d(x / length, y / length, z / length);
	}

	OdGeVector3d OdGeVector3d::CrossProduct(const OdGeVector3d& other) const
	{
		return OdGeVector3d(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	float OdGeVector3d::DotProduct(const OdGeVector3d& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	OdGeVector3d OdGeVector3d::operator-() const
	{
		return OdGeVector3d(-x, -y, -z);
	}

	void OdGeVector3d::operator+=(const OdGeVector3d& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}

	void OdGeVector3d::operator-=(const OdGeVector3d& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}

	OdGeVector3d OdGeVector3d::operator+(const OdGeVector3d& other) const
	{
		return OdGeVector3d(x + other.x, y + other.y, z + other.z);
	}

	OdGeVector3d OdGeVector3d::operator-(const OdGeVector3d& other) const
	{
		return OdGeVector3d(x - other.x, y - other.y, z - other.z);
	}

	OdGeVector3d OdGeVector3d::operator*(float scalar) const
	{
		return OdGeVector3d(x * scalar, y * scalar, z * scalar);
	}

	OdGeVector3d OdGeVector3d::operator/=(const float scale)
	{
		x /= scale;
		y /= scale;
		z /= scale;
		return *this;
	}

	bool OdGeVector3d::IsEqual(const OdGeVector3d& other) const
	{
		return (fabs(x - other.x) < FLT_EPSILON) && (fabs(y - other.y) < FLT_EPSILON) && (fabs(z - other.z) < FLT_EPSILON);
	}
}

