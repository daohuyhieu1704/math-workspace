#include "pch.h"
#include "Quaternion3d.h"
#include "OdGeMatrix3d.h"

namespace GeometryNative
{
	const Quaternion3d Quaternion3d::kIdentity = Quaternion3d();

    Quaternion3d Quaternion3d::fromAxisAngle(double angleRad, OdGeVector3d axis, OdGePoint3d origin)
    {
        double norm = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
        if (norm == 0) throw std::invalid_argument("Axis vector must not be zero!");

        double halfAngle = angleRad / 2.0;
        double sinHalfAngle = std::sin(halfAngle);

        return Quaternion3d(
            std::cos(halfAngle),
            sinHalfAngle * axis.x / norm,
            sinHalfAngle * axis.y / norm,
            sinHalfAngle * axis.z / norm,
			origin
        );
    }

    void Quaternion3d::normalize()
    {
        double norm = std::sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
        if (norm == 0) throw std::runtime_error("Cannot normalize a zero quaternion!");
        m_w /= norm;
        m_x /= norm;
        m_y /= norm;
        m_z /= norm;
    }

    Quaternion3d Quaternion3d::operator*(const Quaternion3d& other) const
    {
        return Quaternion3d(
            m_w * other.m_w - m_x * other.m_x - m_y * other.m_y - m_z * other.m_z,
            m_w * other.m_x + m_x * other.m_w + m_y * other.m_z - m_z * other.m_y,
            m_w * other.m_y - m_x * other.m_z + m_y * other.m_w + m_z * other.m_x,
            m_w * other.m_z + m_x * other.m_y - m_y * other.m_x + m_z * other.m_w
        );
    }

    OdGeVector3d Quaternion3d::rotateVector(double vx, double vy, double vz) const
    {
        Quaternion3d vectorQ(0, vx, vy, vz);
        Quaternion3d result = (*this) * vectorQ * conjugate();
        return OdGeVector3d(result.m_x, result.m_y, result.m_z);
    }

    OdGePoint3d Quaternion3d::operator*(const OdGePoint3d& point) const
    {
        return mult(point);
    }

    OdGeMatrix3d Quaternion3d::toMatrix3d() const
    {
		OdGeMatrix3d mat = OdGeMatrix3d::kIdentity;
        double xx = m_x * m_x;
        double yy = m_y * m_y;
        double zz = m_z * m_z;
        double xy = m_x * m_y;
        double xz = m_x * m_z;
        double yz = m_y * m_z;
        double wx = m_w * m_x;
        double wy = m_w * m_y;
        double wz = m_w * m_z;

        mat[0][0] = 1.0 - 2.0 * (yy + zz);
        mat[0][1] = 2.0 * (xy - wz);
        mat[0][2] = 2.0 * (xz + wy);
        mat[0][3] = 0.0;

        mat[1][0] = 2.0 * (xy + wz);
        mat[1][1] = 1.0 - 2.0 * (xx + zz);
        mat[1][2] = 2.0 * (yz - wx);
        mat[1][3] = 0.0;

        mat[2][0] = 2.0 * (xz - wy);
        mat[2][1] = 2.0 * (yz + wx);
        mat[2][2] = 1.0 - 2.0 * (xx + yy);
        mat[2][3] = 0.0;

        mat[3][0] = 0.0;
        mat[3][1] = 0.0;
        mat[3][2] = 0.0;
        mat[3][3] = 1.0;

        return mat;
    }

    Quaternion3d& Quaternion3d::setToRotateVectorToVector(const OdGeVector3d& fromVec, const OdGeVector3d& toVec, OdGePoint3d origin)
    {
        OdGeVector3d f = fromVec;
        OdGeVector3d t = toVec;

        if (f.Length() < FLT_EPSILON || t.Length() < FLT_EPSILON) {
            *this = Quaternion3d::kIdentity;
            return *this;
        }

        f.normalize();
        t.normalize();
        double dot = f.dotProduct(t);

        if (dot > 0.999999) {
            *this = Quaternion3d::kIdentity;
            return *this;
        }
        if (dot < -0.999999) {
            OdGeVector3d orthogonal = OdGeVector3d::kXAxis;
            if (fabs(f.dotProduct(orthogonal)) > 0.9) {
                orthogonal = OdGeVector3d::kYAxis;
            }
            OdGeVector3d axis = f.crossProduct(orthogonal);
            axis.normalize();
            *this = Quaternion3d::fromAxisAngle(OdPI, axis, origin);
            return *this;
        }

        double angle = std::acos(dot);
        OdGeVector3d axis = f.crossProduct(t);
        if (axis.Length() < FLT_EPSILON) {
            *this = Quaternion3d::kIdentity;
            return *this;
        }

        axis.normalize();
        *this = Quaternion3d::fromAxisAngle(angle, axis, origin);
        return *this;
    }
}
