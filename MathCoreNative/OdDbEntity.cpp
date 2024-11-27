#include "pch.h"
#include "OdDbEntity.h"
#include "OdError.h"

json OdDbEntity::toJson() const
{
    json j;
	j["type"] = getClassName();
    j["scale"] = { {"x", m_scale.sx}, {"y", m_scale.sy}, {"z", m_scale.sz} };
    j["position"] = { {"x", m_position.x}, {"y", m_position.y}, {"z", m_position.z} };
    j["xDir"] = { {"x", m_xDir.x}, {"y", m_xDir.y}, {"z", m_xDir.z} };
    j["yDir"] = { {"x", m_yDir.x}, {"y", m_yDir.y}, {"z", m_yDir.z} };
    j["zDir"] = { {"x", m_zDir.x}, {"y", m_zDir.y}, {"z", m_zDir.z} };
    j["extents"] = {
        {"min", { {"x", m_extents.GetMinPnt().x}, {"y", m_extents.GetMinPnt().y}, {"z", m_extents.GetMinPnt().z} }},
        {"max", { {"x", m_extents.GetMaxPnt().x}, {"y", m_extents.GetMaxPnt().y}, {"z", m_extents.GetMaxPnt().z} }}
    };
    return j;
}

void OdDbEntity::fromJson(const json& j)
{ 
    if (j.contains("scale")) {
        m_scale.sx = j.at("scale").at("x").get<double>();
        m_scale.sy = j.at("scale").at("y").get<double>();
        m_scale.sz = j.at("scale").at("z").get<double>();
    }

    if (j.contains("position")) {
        m_position.x = j.at("position").at("x").get<double>();
        m_position.y = j.at("position").at("y").get<double>();
        m_position.z = j.at("position").at("z").get<double>();
    }

    if (j.contains("xDir")) {
        m_xDir.x = j.at("xDir").at("x").get<double>();
        m_xDir.y = j.at("xDir").at("y").get<double>();
        m_xDir.z = j.at("xDir").at("z").get<double>();
    }

    if (j.contains("yDir")) {
        m_yDir.x = j.at("yDir").at("x").get<double>();
        m_yDir.y = j.at("yDir").at("y").get<double>();
        m_yDir.z = j.at("yDir").at("z").get<double>();
    }

    if (j.contains("zDir")) {
        m_zDir.x = j.at("zDir").at("x").get<double>();
        m_zDir.y = j.at("zDir").at("y").get<double>();
        m_zDir.z = j.at("zDir").at("z").get<double>();
    }

    if (j.contains("extents")) {
		OdGePoint3d minPnt;
		OdGePoint3d maxPnt;
        if (j.at("extents").contains("min")) {
            minPnt = OdGePoint3d(
                    j.at("extents").at("min").at("x").get<double>(),
                    j.at("extents").at("min").at("y").get<double>(),
                    j.at("extents").at("min").at("z").get<double>());
        }
        if (j.at("extents").contains("max")) {
			maxPnt = OdGePoint3d(
				j.at("extents").at("max").at("x").get<double>(),
				j.at("extents").at("max").at("y").get<double>(),
				j.at("extents").at("max").at("z").get<double>());
        }

		m_extents.set(minPnt, maxPnt);
    }
}

OdResult OdDbEntity::transformBy(const OdGeMatrix3d xform)
{
    try {
        m_transform = xform * m_transform;
        return OdResult::eOk;
    }
    catch (...) {
		return OdResult::eInvalidInput;
    }
}

bool OdDbEntity::intersectWithRay(
    double rayStartX, double rayStartY, double rayStartZ,
    double rayDirX, double rayDirY, double rayDirZ,
    double& intersectionDistance)
{
    // Get bounding box extents (min and max points of the bounding box)
    OdGePoint3d minPnt = getExtents().GetMinPnt();
    OdGePoint3d maxPnt = getExtents().GetMaxPnt();

    // Calculate the ray's direction components
    double invDirX = (rayDirX != 0) ? 1.0 / rayDirX : 0.0;
    double invDirY = (rayDirY != 0) ? 1.0 / rayDirY : 0.0;
    double invDirZ = (rayDirZ != 0) ? 1.0 / rayDirZ : 0.0;

    // Calculate the intersection of the ray with the box along each axis
    double tmin = (minPnt.x - rayStartX) * invDirX;
    double tmax = (maxPnt.x - rayStartX) * invDirX;

    if (tmin > tmax) std::swap(tmin, tmax);

    double tymin = (minPnt.y - rayStartY) * invDirY;
    double tymax = (maxPnt.y - rayStartY) * invDirY;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax)) {
        return false; // No intersection
    }

    // Update the tmin and tmax values for the y-direction
    tmin = std::max(tmin, tymin);
    tmax = std::min(tmax, tymax);

    double tzmin = (minPnt.z - rayStartZ) * invDirZ;
    double tzmax = (maxPnt.z - rayStartZ) * invDirZ;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax)) {
        return false; // No intersection
    }

    // Final tmin and tmax values for all axes
    tmin = std::max(tmin, tzmin);
    tmax = std::min(tmax, tzmax);

    if (tmax < 0) {
        return false; // The ray is going away from the box
    }

    // If tmin is positive, it is the first intersection, otherwise use tmax
    intersectionDistance = (tmin >= 0) ? tmin : tmax;
    return true;
}
