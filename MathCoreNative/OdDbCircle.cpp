#include "pch.h"
#include "OdDbCircle.h"

OD_RTTI_DEFINE(OdDbCircle, OdDbEntity)
OdDbCircle::OdDbCircle() : m_center(OdGePoint3d::kOrigin), m_radius(0)
{
	setPosition(OdGePoint3d::kOrigin);
	setXDir(OdGeVector3d::kXAxis);
	setYDir(OdGeVector3d::kYAxis);
	setZDir(OdGeVector3d::kZAxis);
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
	return OdResult::eNotImplementedYet;
}

OdGeExtents3d OdDbCircle::boundingBox() const
{
	OdGePoint3d center = m_center;
	double radius = m_radius;

	OdGePoint3d minPoint(center.x - radius, center.y - radius, center.z);
	OdGePoint3d maxPoint(center.x + radius, center.y + radius, center.z);

	OdGeVector3d xDir = getXDir();
	OdGeVector3d yDir = getYDir();
	OdGeVector3d zDir = getZDir();

	OdGePoint3d transformedMin = center + xDir * -radius + yDir * -radius;
	OdGePoint3d transformedMax = center + xDir * radius + yDir * radius;

	OdGeExtents3d boundingBox = OdGeExtents3d(minPoint, maxPoint);
	return boundingBox;
}

OdResult OdDbCircle::worldDraw() const
{
	return OdResult::eNotImplementedYet;
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
