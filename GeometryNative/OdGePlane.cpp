#include "pch.h"
#include "OdGePlane.h"
#include <cmath>

namespace GeometryNative
{
    OdGePlane::OdGePlane()
        : m_origin(OdGePoint3d::kOrigin), m_normal(OdGeVector3d::kZAxis) {
    }

    OdGePlane::OdGePlane(const OdGePlane& plane)
        : m_origin(plane.m_origin), m_normal(plane.m_normal) {
    }

    OdGePlane::OdGePlane(const OdGePoint3d& origin, const OdGeVector3d& normal)
        : m_origin(origin), m_normal(normal) {
        this->m_normal.normalize();
    }

    OdGePlane::OdGePlane(const OdGePoint3d& uPnt, const OdGePoint3d& origin, const OdGePoint3d& vPnt)
        : m_origin(origin) {
        OdGeVector3d uVec = uPnt - origin;
        OdGeVector3d vVec = vPnt - origin;
        this->m_normal = uVec.crossProduct(vVec);
        this->m_normal.normalize();
    }

    // Constructor with origin, u-axis, and v-axis
    OdGePlane::OdGePlane(const OdGePoint3d& origin, const OdGeVector3d& uAxis, const OdGeVector3d& vAxis)
        : m_origin(origin) {
        this->m_normal = uAxis.crossProduct(vAxis);
        this->m_normal.normalize();
    }

    OdGePlane::OdGePlane(double a, double b, double c, double d) {
        this->m_normal = OdGeVector3d(a, b, c);
        this->m_normal.normalize();
        if (a != 0 || b != 0 || c != 0) {
            double scale = -d / (a * a + b * b + c * c);
            this->m_origin = OdGePoint3d(a * scale, b * scale, c * scale);
        }
        else {
            this->m_origin = OdGePoint3d::kOrigin;
        }
    }

    double OdGePlane::DistanceTo(const OdGePoint3d& point) const
    {	
        // Plane equation: Ax + By + Cz + D = 0
        double a = m_normal.x;
        double b = m_normal.y;
        double c = m_normal.z;
        double d = -(a * m_origin.x + b * m_origin.y + c * m_origin.z);

        // Calculate the distance
        return std::abs(a * point.x + b * point.y + c * point.z + d) / std::sqrt(a * a + b * b + c * c);
    }

    bool OdGePlane::Intersect(const OdGePlane& other, OdGePoint3d& pointOnLine, OdGeVector3d& lineDirection) const
    {
		return Intersect(other, pointOnLine, lineDirection, FLT_EPSILON);
    }

    bool OdGePlane::Intersect(const OdGePlane& other, OdGePoint3d& pointOnLine, OdGeVector3d& lineDirection, const double tolerance) const
    {
        // Compute the direction vector of the intersection line
        lineDirection = m_normal.crossProduct(other.m_normal);

        // Check if the planes are parallel
        if (lineDirection.Length() <= tolerance)
            return false; // No intersection line, planes are parallel or coincident

        // Plane equations: 
        // P1: n1.x * x + n1.y * y + n1.z * z + d1 = 0
        // P2: n2.x * x + n2.y * y + n2.z * z + d2 = 0
        OdGeVector3d originVector = m_origin.toVector3d();
        double d1 = -(m_normal.dotProduct(originVector));
		OdGeVector3d otherOriginVector = other.m_origin.toVector3d();
        double d2 = -(other.m_normal.dotProduct(otherOriginVector));

        // Choose a third axis perpendicular to the intersection direction
        OdGeVector3d axis = lineDirection.normalize();
        OdGeVector3d perpToLine = axis.crossProduct(m_normal).normalize();

        // Solve for a point on the line
        OdGeVector3d n1 = m_normal;
        OdGeVector3d n2 = other.m_normal;

        double denom = n1.crossProduct(n2).Length();
        if (denom < tolerance)
            return false; // Planes are parallel

        // Combine plane equations to find a point on the line
        double c1 = (d2 * n2.Length() - d1 * n1.Length()) / denom;
        double c2 = (d1 * n2.Length() - d2 * n1.Length()) / denom;

        OdGeVector3d p = (c1 * n1 + c2 * n2);
        pointOnLine = m_origin + p;

        return true;
    }

    std::optional<OdGePoint3d> OdGePlane::intersectWith(const OdGePoint3d& rayOrigin, const OdGeVector3d& rayDir, double& t) const {
        double denominator = m_normal.dotProduct(rayDir);
        if (std::abs(denominator) < 1e-6) return std::nullopt;

        OdGeVector3d diff = m_origin - rayOrigin;
        t = m_normal.dotProduct(diff) / denominator;

        // If t < 0, the intersection is behind the ray's origin
        if (t < 0) return std::nullopt;

        OdGePoint3d intersection = rayOrigin + t * rayDir;
        return intersection;
    }

    const OdGePlane OdGePlane::kXYPlane = OdGePlane(OdGePoint3d::kOrigin, OdGeVector3d::kZAxis);
    const OdGePlane OdGePlane::kYZPlane = OdGePlane(OdGePoint3d::kOrigin, OdGeVector3d::kXAxis);
    const OdGePlane OdGePlane::kZXPlane = OdGePlane(OdGePoint3d::kOrigin, OdGeVector3d::kYAxis);
}

