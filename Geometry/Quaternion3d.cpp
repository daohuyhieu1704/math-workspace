#include "pch.h"
#include "Quaternion3d.h"

namespace Geometry
{
	Quaternion3d Quaternion3d::FromAxisAngle(double angleRad, Vector3d axis, Point3d origin)
	{
		GeometryNative::OdGeVector3d nativeAxis(axis.X, axis.Y, axis.Z);
		GeometryNative::OdGePoint3d nativeOrigin(origin.X, origin.Y, origin.Z);
		auto nativeQuat = GeometryNative::Quaternion3d::fromAxisAngle(angleRad, nativeAxis, nativeOrigin);
		return Quaternion3d(nativeQuat.m_w, nativeQuat.m_x, nativeQuat.m_y, nativeQuat.m_z);
	}

	void Quaternion3d::Normalize()
	{
		GeometryNative::Quaternion3d nativeQuat(m_w, m_x, m_y, m_z);
		nativeQuat.normalize();
		m_w = nativeQuat.m_w;
		m_x = nativeQuat.m_x;
		m_y = nativeQuat.m_y;
		m_z = nativeQuat.m_z;
	}

	Quaternion3d Quaternion3d::operator*(Quaternion3d other)
	{
		GeometryNative::Quaternion3d nativeQuat1(m_w, m_x, m_y, m_z);
		GeometryNative::Quaternion3d nativeQuat2(other.m_w, other.m_x, other.m_y, other.m_z);
		auto result = nativeQuat1 * nativeQuat2;
		return Quaternion3d(result.m_w, result.m_x, result.m_y, result.m_z);
	}

	Point3d Quaternion3d::RotatePoint(Point3d point)
	{
		GeometryNative::Quaternion3d nativeQuat(m_w, m_x, m_y, m_z);
		GeometryNative::OdGePoint3d nativePoint = GeometryNative::OdGePoint3d(point.X, point.Y, point.Z);
		GeometryNative::OdGePoint3d result = nativeQuat.mult(nativePoint);
		return Point3d(result.x, result.y, result.z);
	}

	Matrix3d Quaternion3d::ToMatrix3d()
	{
		GeometryNative::Quaternion3d nativeQuat(m_w, m_x, m_y, m_z);
		GeometryNative::OdGeMatrix3d mat = nativeQuat.toMatrix3d();
		array<double, 2>^ entries = gcnew array<double, 2>(4, 4);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				entries[i, j] = mat[i][j];
			}
		}
		return Matrix3d(entries);
	}
}