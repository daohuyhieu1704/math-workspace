#include "pch.h"
#include "OdDbArc.h"

OdDbArc::OdDbArc()
{
	setPosition(OdGePoint3d::kOrigin);
	m_bulge = 0;
	m_startPnt = OdGePoint3d::kOrigin;
}

OdBaseObjectPtr OdDbArc::Clone()
{
	OdDbArcPtr pClone = OdDbArc::createObject();
	pClone->setBulge(getBulge());
	pClone->setStartPoint(getStartPoint());
    return pClone;
}

OdResult OdDbArc::draw() 
{
	return OdResult::eNotImplementedYet;
}

OdGeExtents3d OdDbArc::boundingBox() const
{
	return OdGeExtents3d(m_startPnt, m_endPnt);
}

json OdDbArc::toJson() const
{
	json j = OdDbEntity::toJson();
	j["bulge"] = m_bulge;
	j["startPnt"] = { {"x", m_startPnt.x}, {"y", m_startPnt.y}, {"z", m_startPnt.z} };
	return j;
}

void OdDbArc::fromJson(const json& j)
{
	OdDbEntity::fromJson(j);
	if (j.contains("bulge")) {
		m_bulge = j.at("bulge").get<double>();
	}
	if (j.contains("startPnt")) {
		m_startPnt = OdGePoint3d(
			j.at("startPnt").at("x").get<double>(),
			j.at("startPnt").at("y").get<double>(),
			j.at("startPnt").at("z").get<double>()
		);
	}
}
