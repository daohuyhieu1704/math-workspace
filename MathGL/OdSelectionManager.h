#pragma once

#include <vector>
#include <OdGePoint3d.h>
#include <OdGePlane.h>
#include <OdGeExtents3d.h>

using namespace GeometryNative;

class OdSelectionManager {
public:
    /// <summary>
    /// 
    /// </summary>
    /// <param name="points"></param>
    /// <param name="faces"></param>
    OdSelectionManager(const std::vector<OdGePoint3d>& points, const std::vector<std::vector<int>>& faces)
        : m_points(points), m_faces(faces) {
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="points"></param>
    /// <param name="faces"></param>
    OdSelectionManager(OdGeExtents3d exts) {
        m_points = exts.getPoints();
		m_faces = exts.getFaces();
    }
    /// <summary>
    /// 
    /// </summary>
    /// <param name="testPoint"></param>
    /// <returns></returns>
    bool isPointInside(const OdGePoint3d& testPoint) const {
        int numIntersections = 0;
        for (const auto& face : m_faces) {
            std::vector<OdGePoint3d> facePoints;
            for (int idx : face) {
                facePoints.push_back(m_points[idx]);
            }

            if (doesRayIntersectFace(testPoint, facePoints)) {
                ++numIntersections;
            }
        }

        return (numIntersections % 2) == 1;
    }

private:
    std::vector<OdGePoint3d> m_points;
    std::vector<std::vector<int>> m_faces;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="testPoint"></param>
    /// <param name="facePoints"></param>
    /// <returns></returns>
    bool doesRayIntersectFace(const OdGePoint3d& testPoint, const std::vector<OdGePoint3d>& facePoints) const {
        if (facePoints.size() < 3) {
            return false;
        }

        OdGePlane facePlane(facePoints[0], facePoints[1], facePoints[2]);

        OdGePoint3d intersectionPoint;
        if (!rayIntersectsPlane(testPoint, facePlane, intersectionPoint)) {
            return false;
        }

        return isPointInsideFace(intersectionPoint, facePoints);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="testPoint"></param>
    /// <param name="plane"></param>
    /// <param name="intersectionPoint"></param>
    /// <returns></returns>
    bool rayIntersectsPlane(const OdGePoint3d& testPoint, const OdGePlane& plane, OdGePoint3d& intersectionPoint) const {
        // Define the ray direction (e.g., along X-axis)
        OdGeVector3d rayDir(1.0, 0.0, 0.0);

        // Calculate the ray-plane intersection
        double t;
        if (!plane.intersectWith(testPoint, rayDir, t)) {
            return false; // No intersection
        }

        // Compute the intersection point
        intersectionPoint = testPoint + t * rayDir;
        return true;
    }

    /// <summary>
    /// Check if a point is inside a face
    /// </summary>
    /// <param name="point"></param>
    /// <param name="facePoints"></param>
    /// <returns></returns>
    bool isPointInsideFace(const OdGePoint3d& point, const std::vector<OdGePoint3d>& facePoints) const {
        // Project to 2D (e.g., ignore the Z-coordinate)
        std::vector<OdGePoint2d> projectedPoints;
        for (const auto& p : facePoints) {
            projectedPoints.emplace_back(p.x, p.y);
        }

        // Use 2D point-in-polygon logic
        return isPointInside2D(point.x, point.y, projectedPoints);
    }

    /// <summary>
    /// Check if a 2D point is inside a polygon
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="polygon"></param>
    /// <returns></returns>
    bool isPointInside2D(double x, double y, const std::vector<OdGePoint2d>& polygon) const {
        int numIntersections = 0;
        size_t numVertices = polygon.size();

        for (size_t i = 0; i < numVertices; ++i) {
            const OdGePoint2d& v1 = polygon[i];
            const OdGePoint2d& v2 = polygon[(i + 1) % numVertices];

            if ((y > v1.y) != (y > v2.y) &&
                (x < (v2.x - v1.x) * (y - v1.y) / (v2.y - v1.y) + v1.x)) {
                ++numIntersections;
            }
        }

        return (numIntersections % 2) == 1;
    }
};
