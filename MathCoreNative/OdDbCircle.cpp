#include "pch.h"
#include "OdDbCircle.h"

OD_RTTI_DEFINE(OdDbCircle, OdDbEntity)
OdDbCircle::OdDbCircle() : m_center(OdGePoint3d::kOrigin), m_radius(0)
{
	setPosition(OdGePoint3d::kOrigin);
}

OdBaseObjectPtr OdDbCircle::Clone()
{
	OdDbCirclePtr clone = OdDbCircle::createObject();
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
	clone->setCenter(m_center);
	clone->setRadius(m_radius);
	return clone;
}

OdResult OdDbCircle::draw() const
{
	return OdResult::eInvalidDrawing;
}

OdGeExtents3d OdDbCircle::boundingBox() const
{
	return getExtents();
}

OdResult OdDbCircle::worldDraw() const
{
	return OdResult::eInvalidDrawing;
}

json OdDbCircle::toJson() const
{
	json j = OdDbEntity::toJson();
	j["center"] = { {"x", m_center.x}, {"y", m_center.y}, {"z", m_center.z} };
	j["radius"] = m_radius;
	return j;
}

void OdDbCircle::fromJson(const json& j)
{
	OdDbEntity::fromJson(j);
	if (j.contains("center")) {
		m_center = OdGePoint3d(
			j.at("center").at("x").get<double>(),
			j.at("center").at("y").get<double>(),
			j.at("center").at("z").get<double>()
		);
	}
	if (j.contains("radius")) {
		m_radius = j.at("radius").get<double>();
	}
}
