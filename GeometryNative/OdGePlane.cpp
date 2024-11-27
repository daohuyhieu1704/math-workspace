#include "pch.h"
#include "OdGePlane.h"
#include <cmath>

namespace GeometryNative
{
    OdGePlane::OdGePlane()
        : origin(OdGePoint3d::kOrigin), normal(OdGeVector3d::kZAxis) {
    }

    OdGePlane::OdGePlane(const OdGePlane& plane)
        : origin(plane.origin), normal(plane.normal) {
    }

    OdGePlane::OdGePlane(const OdGePoint3d& origin, const OdGeVector3d& normal)
        : origin(origin), normal(normal) {
        this->normal.normalize();
    }

    OdGePlane::OdGePlane(const OdGePoint3d& uPnt, const OdGePoint3d& origin, const OdGePoint3d& vPnt)
        : origin(origin) {
        OdGeVector3d uVec = uPnt - origin;
        OdGeVector3d vVec = vPnt - origin;
        this->normal = uVec.crossProduct(vVec);
        this->normal.normalize();
    }

    // Constructor with origin, u-axis, and v-axis
    OdGePlane::OdGePlane(const OdGePoint3d& origin, const OdGeVector3d& uAxis, const OdGeVector3d& vAxis)
        : origin(origin) {
        this->normal = uAxis.crossProduct(vAxis);
        this->normal.normalize();
    }

    OdGePlane::OdGePlane(double a, double b, double c, double d) {
        this->normal = OdGeVector3d(a, b, c);
        this->normal.normalize();
        if (a != 0 || b != 0 || c != 0) {
            double scale = -d / (a * a + b * b + c * c);
            this->origin = OdGePoint3d(a * scale, b * scale, c * scale);
        }
        else {
            this->origin = OdGePoint3d::kOrigin;
        }
    }

    double OdGePlane::DistanceTo(const OdGePoint3d& point) const
    {	
        // Plane equation: Ax + By + Cz + D = 0
        double a = normal.x;
        double b = normal.y;
        double c = normal.z;
        double d = -(a * origin.x + b * origin.y + c * origin.z);

        // Calculate the distance
        return std::abs(a * point.x + b * point.y + c * point.z + d) / std::sqrt(a * a + b * b + c * c);
    }

    bool OdGePlane::Intersect(const OdGePlane& other, OdGePoint3d& pointOnLine, OdGeVector3d& lineDirection, const double tolerance) const
    {
        // Compute the direction vector of the intersection line
        lineDirection = normal.crossProduct(other.normal);

        // Check if the planes are parallel
        if (lineDirection.Length() <= tolerance)
            return false; // No intersection line, planes are parallel or coincident

        // Plane equations: 
        // P1: n1.x * x + n1.y * y + n1.z * z + d1 = 0
        // P2: n2.x * x + n2.y * y + n2.z * z + d2 = 0
        OdGeVector3d originVector = origin.toVector3d();
        double d1 = -(normal.dotProduct(originVector));
		OdGeVector3d otherOriginVector = other.origin.toVector3d();
        double d2 = -(other.normal.dotProduct(otherOriginVector));

        // Choose a third axis perpendicular to the intersection direction
        OdGeVector3d axis = lineDirection.normalize();
        OdGeVector3d perpToLine = axis.crossProduct(normal).normalize();

        // Solve for a point on the line
        OdGeVector3d n1 = normal;
        OdGeVector3d n2 = other.normal;

        double denom = n1.crossProduct(n2).Length();
        if (denom < tolerance)
            return false; // Planes are parallel

        // Combine plane equations to find a point on the line
        double c1 = (d2 * n2.Length() - d1 * n1.Length()) / denom;
        double c2 = (d1 * n2.Length() - d2 * n1.Length()) / denom;

        OdGeVector3d p = (c1 * n1 + c2 * n2);
        pointOnLine = origin + p;

        return true;
    }


    const OdGePlane OdGePlane::kXYPlane = OdGePlane(OdGePoint3d::kOrigin, OdGeVector3d::kZAxis);
    const OdGePlane OdGePlane::kYZPlane = OdGePlane(OdGePoint3d::kOrigin, OdGeVector3d::kXAxis);
    const OdGePlane OdGePlane::kZXPlane = OdGePlane(OdGePoint3d::kOrigin, OdGeVector3d::kYAxis);
}

