#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "OdGePoint3d.h"
#include <vector>

namespace GeometryNative
{
    class Quaternion3d
    {
    public:
        double m_w, m_x, m_y, m_z;
		OdGePoint3d m_origin = OdGePoint3d::kOrigin;
		static const Quaternion3d kIdentity;
        /// <summary>
		/// Identity quaternion
        /// </summary>
        Quaternion3d() : m_w(1), m_x(0), m_y(0), m_z(0) {}

        Quaternion3d(double w, double x, double y, double z, OdGePoint3d origin = OdGePoint3d::kOrigin) 
            : m_w(w), m_x(x), m_y(y), m_z(z),
			m_origin(origin)
        {}

        static Quaternion3d fromAxisAngle(double angleRad, OdGeVector3d axis, OdGePoint3d origin = OdGePoint3d::kOrigin);

        /// <summary>
        /// Normalize the quaternion
        /// </summary>
        void normalize();

        /// <summary>
        /// Get the magnitude of the quaternion
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        Quaternion3d operator*(const Quaternion3d& other) const;

        /// <summary>
        /// Rotate a vector by this quaternion
        /// </summary>
        /// <param name="vx"></param>
        /// <param name="vy"></param>
        /// <param name="vz"></param>
        /// <returns></returns>
        OdGeVector3d rotateVector(double vx, double vy, double vz) const;

        /// <summary>
        /// Get the conjugate of the quaternion
        /// </summary>
        /// <returns></returns>
        Quaternion3d conjugate() const {
            return Quaternion3d(m_w, -m_x, -m_y, -m_z);
        }

        /// <summary>
        /// Rotate an OdGePoint3d by this quaternion
        /// </summary>
        /// <param name="point"></param>
        /// <returns></returns>
        OdGePoint3d mult(const OdGePoint3d& point) const {
            auto [rx, ry, rz] = rotateVector(point.x, point.y, point.z);
            return OdGePoint3d(rx, ry, rz);
        }

        /// <summary>
        /// Rotate a vector of OdGePoint3d by this quaternion
        /// </summary>
        /// <param name="points"></param>
        /// <returns></returns>
        std::vector<OdGePoint3d> mult(const std::vector<OdGePoint3d>& points) const {
            std::vector<OdGePoint3d> rotatedPoints;
            for (const auto& point : points) {
                rotatedPoints.push_back(mult(point));
            }
            return rotatedPoints;
        }

        /// <summary>
        /// Overload operator* to rotate an OdGePoint3d
        /// </summary>
        /// <param name="point"></param>
        /// <returns></returns>
        OdGePoint3d operator*(const OdGePoint3d& point) const;

        /// <summary>
		/// Convert the quaternion to a rotation matrix
        /// </summary>
        /// <returns></returns>
        OdGeMatrix3d toMatrix3d() const;

        Quaternion3d& setToRotateVectorToVector(const OdGeVector3d& fromVec, const OdGeVector3d& toVec, OdGePoint3d origin);
    };
}
