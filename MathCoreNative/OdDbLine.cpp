#include "pch.h"
#include "OdDbLine.h"

OdDbLine::OdDbLine()
{
	setPosition(OdGePoint3d::kOrigin);
	m_startPnt = OdGePoint3d::kOrigin;
	m_endPnt = OdGePoint3d::kOrigin;
}

OdBaseObjectPtr OdDbLine::Clone()
{
	OdDbLinePtr pLine = OdDbLine::createObject();
	pLine->setStartPnt(m_startPnt);
	pLine->setEndPnt(m_endPnt);
	return pLine;
}

OdResult OdDbLine::draw() 
{
	return OdResult::eNotImplementedYet;
}

json OdDbLine::toJson() const
{
	json j = OdDbEntity::toJson();
	j["startPnt"] = { {"x", m_startPnt.x}, {"y", m_startPnt.y}, {"z", m_startPnt.z} };
	j["endPnt"] = { {"x", m_endPnt.x}, {"y", m_endPnt.y}, {"z", m_endPnt.z} };
	return j;
}

void OdDbLine::fromJson(const json& j)
{
	OdDbEntity::fromJson(j);
	if (j.contains("startPnt")) {
		m_startPnt = OdGePoint3d(
			j.at("startPnt").at("x").get<double>(),
			j.at("startPnt").at("y").get<double>(),
			j.at("startPnt").at("z").get<double>()
		);
	}
	if (j.contains("endPnt")) {
		m_endPnt = OdGePoint3d(
			j.at("endPnt").at("x").get<double>(),
			j.at("endPnt").at("y").get<double>(),
			j.at("endPnt").at("z").get<double>()
		);
	}
}
