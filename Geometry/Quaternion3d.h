#pragma once
#include <Quaternion3d.h>
#include <OdGePoint3d.h>
#include "Matrix3d.h"

namespace Geometry
{
	public value class Quaternion3d
	{
		double m_w, m_x, m_y, m_z;
        Point3d m_origin;
    public:
        // Constructor
        Quaternion3d(double w, double x, double y, double z)
            : m_w(w), m_x(x), m_y(y), m_z(z) {
        }

        // Convert from Axis-Angle to Quaternion
        static Quaternion3d FromAxisAngle(double angleRad, Vector3d axis, Point3d origin);

        // Normalize the quaternion
        void Normalize();

        // Multiply by another Quaternion3dWrapper
        Quaternion3d operator*(Quaternion3d other);

        // Rotate a point
        Point3d RotatePoint(Point3d point);

        // Convert to a 3D rotation matrix
        Matrix3d ToMatrix3d();
    };
}