#include "pch.h"
#include "OdGeExtents2d.h"

namespace GeometryNative
{
	OdGePoint2d OdGeExtents2d::GetMinPnt() const
	{
		return m_min;
	}

	void OdGeExtents2d::SetMinPnt(OdGePoint2d minPnt)
	{
		m_min = minPnt;
	}

	OdGePoint2d OdGeExtents2d::GetMaxPnt() const
	{
		return m_max;
	}

	void OdGeExtents2d::SetMaxPnt(OdGePoint2d maxPnt)
	{
		m_max = maxPnt;
	}

	OdGePoint2d OdGeExtents2d::center() const
	{
		return OdGePoint2d((m_min.x + m_max.x) / 2, (m_min.y + m_max.y) / 2);
	}

	OdGeExtents2d::OdGeExtents2d(OdGePoint2d minPnt, OdGePoint2d maxPnt)
	{
		m_min = minPnt;
		m_max = maxPnt;
	}

	OdGeExtents2d::~OdGeExtents2d()
	{
	}
}