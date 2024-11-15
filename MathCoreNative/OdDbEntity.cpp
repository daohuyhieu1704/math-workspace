#include "pch.h"
#include "OdDbEntity.h"
#include "OdError.h"

json OdDbEntity::toJson() const
{
    json j;
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
        //m_position = xform * m_position;

        //m_xDir = xform * m_xDir;
        //m_yDir = xform * m_yDir;
        //m_zDir = xform * m_zDir;

        //m_xDir.Normalize();
        //m_yDir.Normalize();
        //m_zDir.Normalize();

        //OdGePoint3d minPnt = m_extents.GetMinPnt();
        //OdGePoint3d maxPnt = m_extents.GetMaxPnt();
        //m_extents.set(xform * minPnt, xform * maxPnt);
        m_transform = xform * m_transform;
        return OdResult::eOk;
    }
    catch (...) {
		return OdResult::eInvalidInput;
    }
}
