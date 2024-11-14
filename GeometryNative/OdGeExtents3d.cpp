#include "pch.h"
#include "OdGeExtents3d.h"

namespace Geometry
{
	void OdGeExtents3d::set(const OdGePoint3d& min, const OdGePoint3d& max)
	{
		m_min = min;
		m_max = max;
	}
	OdGeExtents3d& OdGeExtents3d::addPoint(const OdGePoint3d& point)
	{
		if ((m_max.x < m_min.x) || (m_max.y < m_min.y) || (m_max.z < m_min.z))
		{
			m_max = m_min = point;
		}
		else
		{
			m_min.x = std::min(m_min.x, point.x);
			m_max.x = std::max(m_max.x, point.x);
			m_min.y = std::min(m_min.y, point.y);
			m_max.y = std::max(m_max.y, point.y);
			m_min.z = std::min(m_min.z, point.z);
			m_max.z = std::max(m_max.z, point.z);
		}
		return *this;
	}
	void OdGeExtents3d::expandBy(const OdGeVector3d& vect)
	{
		OdGePoint3d p1 = m_min, p2 = m_max;
		addPoint(p1 + vect);
		addPoint(p2 + vect);
	}
	OdGePoint3d OdGeExtents3d::getCenter() const
	{
		return m_min.CenterTo(m_max);
	}
}