#include "pch.h"
#include "OdGeExtents3d.h"

namespace GeometryNative
{
	void OdGeExtents3d::appendPoint(const OdGePoint3d& point)
	{
		m_points.push_back(point);
	}

	OdGeExtents3d::OdGeExtents3d()
	{
		m_min = OdGePoint3d::kOrigin;
		m_max = OdGePoint3d::kOrigin;
	}

	void OdGeExtents3d::set(const OdGePoint3d& min, const OdGePoint3d& max)
	{
		m_min = min;
		m_max = max;
	}
	OdGeExtents3d& OdGeExtents3d::appendPoint_s(OdGePoint3d point)
	{
		m_min.x = std::min(m_min.x, point.x);
		m_max.x = std::max(m_max.x, point.x);
		m_min.y = std::min(m_min.y, point.y);
		m_max.y = std::max(m_max.y, point.y);
		m_min.z = std::min(m_min.z, point.z);
		m_max.z = std::max(m_max.z, point.z);

		m_points.push_back(point);
		return *this;
	}
	void OdGeExtents3d::expandBy(const OdGeVector3d& vect)
	{
		OdGePoint3d p1 = m_min, p2 = m_max;
		appendPoint_s(p1 + vect);
		appendPoint_s(p2 + vect);
	}
	void OdGeExtents3d::appendFace(
		const std::vector<int>& face)
	{
		m_faces.push_back(face);
	}
	double OdGeExtents3d::getRadius() const
	{
		return m_min.DistanceTo(m_max) / 2.0;
	}
	OdGePoint3d OdGeExtents3d::getCenter() const
	{
		return m_min.CenterTo(m_max);
	}
	void OdGeExtents3d::reset()
	{
		m_min = OdGePoint3d::kOrigin;
		m_max = OdGePoint3d::kOrigin;
		m_points.clear();
		m_faces.clear();
	}
	int OdGeExtents3d::pntSize() const
	{
		return m_points.size();
	}
}