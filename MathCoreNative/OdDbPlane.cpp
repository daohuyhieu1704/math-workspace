#include "pch.h"
#include "OdDbPlane.h"

OD_RTTI_DEFINE(OdDbPlane, OdDbEntity)
OdDbPlane::OdDbPlane() : m_origin(OdGePoint3d::kOrigin), m_normal(OdGeVector3d::kZAxis)
{
	setPosition(OdGePoint3d::kOrigin);
}

OdBaseObjectPtr OdDbPlane::Clone()
{
	OdDbPlanePtr clone = OdDbPlane::createObject();
	OdGeScale3d scale = getScale();
	clone->setScale(scale);
	OdGeExtents3d exts = getExtents();
	clone->setExtents(exts);
	OdGeVector3d xDir = getXDir();
	clone->setXDir(xDir);
	OdGeVector3d yDir = getYDir();
	clone->setYDir(yDir);
	OdGeVector3d zDir = getZDir();
	clone->setZDir(zDir);
	clone->setOrigin(m_origin);
	clone->setNormal(m_normal);
	return clone;
}

OdResult OdDbPlane::draw() 
{
	return OdResult::eNotImplementedYet;
}

json OdDbPlane::toJson() const
{
	json j = OdDbEntity::toJson();
	j["origin"] = { {"x", m_origin.x}, {"y", m_origin.y}, {"z", m_origin.z} };
	j["normal"] = { {"x", m_normal.x}, {"y", m_normal.y}, {"z", m_normal.z} };
	return j;
}

void OdDbPlane::fromJson(const json& j)
{
	OdDbEntity::fromJson(j);
	if (j.contains("origin")) {
		m_origin = OdGePoint3d(
			j.at("origin").at("x").get<double>(),
			j.at("origin").at("y").get<double>(),
			j.at("origin").at("z").get<double>()
		);
	}
	if (j.contains("normal")) {
		m_normal = OdGeVector3d(
			j.at("normal").at("x").get<double>(),
			j.at("normal").at("y").get<double>(),
			j.at("normal").at("z").get<double>()
		);
	}
}
