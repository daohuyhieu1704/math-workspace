#include "pch.h"
#include "Quaternion3d.h"

namespace GeometryNative
{
    Quaternion3d Quaternion3d::fromAxisAngle(double angleRad, double axisX, double axisY, double axisZ)
    {
        double norm = std::sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
        if (norm == 0) throw std::invalid_argument("Axis vector must not be zero!");

        double halfAngle = angleRad / 2.0;
        double sinHalfAngle = std::sin(halfAngle);

        return Quaternion3d(
            std::cos(halfAngle),
            sinHalfAngle * axisX / norm,
            sinHalfAngle * axisY / norm,
            sinHalfAngle * axisZ / norm
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
}
