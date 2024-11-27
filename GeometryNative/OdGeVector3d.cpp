#include "pch.h"
#include "OdGeVector3d.h"

namespace GeometryNative
{
	const OdGeVector3d OdGeVector3d::kXAxis = OdGeVector3d(1.0f, 0.0f, 0.0f);
	const OdGeVector3d OdGeVector3d::kYAxis = OdGeVector3d(0.0f, 1.0f, 0.0f);
	const OdGeVector3d OdGeVector3d::kZAxis = OdGeVector3d(0.0f, 0.0f, 1.0f);

	OdGeVector3d::OdGeVector3d()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	OdGeVector3d::OdGeVector3d(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	OdGeVector3d::~OdGeVector3d()
	{
	}

	double OdGeVector3d::Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	OdGeVector3d OdGeVector3d::normalize() const
	{
		double length = Length();
		return OdGeVector3d(x / length, y / length, z / length);
	}

	OdGeVector3d OdGeVector3d::crossProduct(const OdGeVector3d& other) const
	{
		return OdGeVector3d(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	double OdGeVector3d::dotProduct(const OdGeVector3d& other) const
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

	OdGeVector3d OdGeVector3d::operator*(double scalar) const
	{
		return OdGeVector3d(x * scalar, y * scalar, z * scalar);
	}

	OdGeVector3d OdGeVector3d::operator/=(const double scale)
	{
		x /= scale;
		y /= scale;
		z /= scale;
		return *this;
	}

	bool OdGeVector3d::isEqual(const OdGeVector3d& other) const
	{
		return (fabs(x - other.x) < FLT_EPSILON) && (fabs(y - other.y) < FLT_EPSILON) && (fabs(z - other.z) < FLT_EPSILON);
	}
	bool OdGeVector3d::isParallelTo(const OdGeVector3d& vector) const
	{
		return crossProduct(vector).Length() < FLT_EPSILON;
	}
	OdGeVector3d operator*(double scalar, const OdGeVector3d& vector)
	{
		return OdGeVector3d(scalar * vector.x, scalar * vector.y, scalar * vector.z);
	}
}

