#include "pch.h"
#include "OdGePlane.h"

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

    const OdGePlane OdGePlane::kXYPlane = OdGePlane(OdGePoint3d::kOrigin, OdGeVector3d::kZAxis);
    const OdGePlane OdGePlane::kYZPlane = OdGePlane(OdGePoint3d::kOrigin, OdGeVector3d::kXAxis);
    const OdGePlane OdGePlane::kZXPlane = OdGePlane(OdGePoint3d::kOrigin, OdGeVector3d::kYAxis);
}

