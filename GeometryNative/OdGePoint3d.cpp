#include "pch.h"
#include "OdGePoint3d.h"
#include "OdGeScale3d.h"

namespace GeometryNative
{
	const OdGePoint3d OdGePoint3d::kOrigin = OdGePoint3d();
	OdGePoint3d::OdGePoint3d()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	OdGePoint3d::OdGePoint3d(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	OdGePoint3d::~OdGePoint3d()
	{
	}

	double OdGePoint3d::DistanceTo(OdGePoint3d other) const
	{
		double dx = x - other.x;
		double dy = y - other.y;
		double dz = z - other.z;
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

	OdGePoint3d OdGePoint3d::operator*(const OdGeMatrix3d& matrix) const
	{
		double kx = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
		double ky = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];
		double kz = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z + matrix[2][3];
		double kw = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3];

		// homogeneous coordinates
		if (kw != 1.0 && kw != 0.0)
		{
			kx /= kw;
			ky /= kw;
			kz /= kw;
		}

		return OdGePoint3d(kx, ky, kz);
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

	OdGePoint3d OdGePoint3d::operator*(double scalar) const
	{
		return OdGePoint3d(x * scalar, y * scalar, z * scalar);
	}

	OdGePoint3d OdGePoint3d::operator*(OdGeScale3d scale) const
	{
		return OdGePoint3d(x * scale.sx, y * scale.sy, z * scale.sz);
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

	OdGePoint3d OdGePoint3d::operator-(const OdGeVector3d& vec) const {
		return OdGePoint3d(x - vec.x, y - vec.y, z - vec.z);
	}

	bool OdGePoint3d::isEqual(const OdGePoint3d& other) const
	{
		const double EPSILON = 0.00001f;
		return fabs(x - other.x) < EPSILON && fabs(y - other.y) < EPSILON && fabs(z - other.z) < EPSILON;
	}
	OdGeVector3d OdGePoint3d::toVector3d() const
	{
		return OdGeVector3d(x, y, z);
	}
}