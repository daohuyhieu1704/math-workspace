#include "pch.h"
#include "OdGeExtend2d.h"

namespace Geometry
{
	OdGePoint2d OdGeExtend2d::GetMinPnt() const
	{
		return m_min;
	}

	void OdGeExtend2d::SetMinPnt(OdGePoint2d minPnt)
	{
		m_min = minPnt;
	}

	OdGePoint2d OdGeExtend2d::GetMaxPnt() const
	{
		return m_max;
	}

	void OdGeExtend2d::SetMaxPnt(OdGePoint2d maxPnt)
	{
		m_max = maxPnt;
	}

	OdGeExtend2d::OdGeExtend2d(OdGePoint2d minPnt, OdGePoint2d maxPnt)
	{
		m_min = minPnt;
		m_max = maxPnt;
	}

	OdGeExtend2d::~OdGeExtend2d()
	{
	}
}