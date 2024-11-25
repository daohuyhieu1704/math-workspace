#include "pch.h"
#include "MathArc.h"

namespace MathGL
{
	Point3d MathArc::StartPnt::get()
	{
		return Point3d(GetImpObj()->getStartPoint().x, GetImpObj()->getStartPoint().y, GetImpObj()->getStartPoint().z);
	}
	void MathArc::StartPnt::set(Point3d value)
	{
		GetImpObj()->setStartPoint(OdGePoint3d(value.X, value.Y, value.Z));
	}
	Point3d MathArc::EndPnt::get()
	{
		return Point3d(GetImpObj()->getEndPoint().x, GetImpObj()->getEndPoint().y, GetImpObj()->getEndPoint().z);
	}
	void MathArc::EndPnt::set(Point3d value)
	{
		GetImpObj()->setEndPoint(OdGePoint3d(value.X, value.Y, value.Z));
	}
	double MathArc::Bulge::get()
	{
		return GetImpObj()->getBulge();
	}
	void MathArc::Bulge::set(double value)
	{
		GetImpObj()->setBulge(value);
	}
	void MathArc::Draw()
	{
		OdDrawingManager::R()->appendEntity(GetImpObj()->Clone());
	}
}
