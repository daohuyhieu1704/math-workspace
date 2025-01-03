#include "pch.h"
#include "OdPointPrompt.h"
#include "OdDrawingManager.h"

std::vector<OdGePoint3d> OdPointPrompt::m_points;
OdGePoint3d OdPointPrompt::m_lastPoint;
int OdPointPrompt::m_totalPick = 1;
bool OdPointPrompt::pointPicked = false;


OdPointPrompt::OdPointPrompt()
{
}

OdBaseObjectPtr OdPointPrompt::Clone()
{
	OdPointPromptPtr clone = OdPointPrompt::createObject();
	return clone;
}

OdGePoint3d OdPointPrompt::getPoints()
{
	if (m_points.size() == 0)
	{
		return OdGePoint3d(0.0, 0.0, 0.0);
	}
	OdGePoint3d LastPoint = m_points[m_points.size() - 1];
	return LastPoint;
}

void OdPointPrompt::Focus()
{
}

void OdPointPrompt::AppendPoint(const OdGePoint3d point)
{
	m_points.push_back(point);
	m_lastPoint = point;
	if (m_points.size() == m_totalPick) OdDrawingManager::R()->TriggerPointPicked(m_points);
}

OdGePoint3d OdPointPrompt::LastPoint()
{
	return m_lastPoint;
}

void OdPointPrompt::Clear()
{
	m_points.clear();
}

void OdPointPrompt::TotalPick(int total)
{
	m_totalPick = total;
}

void OdPointPrompt::SetEntityPicked(bool picked)
{
	pointPicked = picked;
}
