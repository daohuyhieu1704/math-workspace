#include "pch.h"
#include "MathCircle.h"

namespace MathGL
{

    Point3d MathCircle::Center::get()
    {
		OdMathCircle* pCircle = GetImpObj();
		return Point3d(pCircle->getCenter().x, pCircle->getCenter().y, pCircle->getCenter().z);
    }

    void MathCircle::Center::set(Point3d value)
    {
		OdGePoint3d center = OdGePoint3d(value.X, value.Y, value.Z);
		GetImpObj()->setCenter(center);
    }

    double MathCircle::Radius::get()
    {
		double minScale = std::min(GetImpObj()->getScale().sx, GetImpObj()->getScale().sy);
		return GetImpObj()->getRadius() * minScale;
    }

    void MathCircle::Radius::set(double value)
    {
		GetImpObj()->setRadius(value);
    }

    int MathCircle::Segments::get()
    {
		return GetImpObj()->getSegments();
    }

    void MathCircle::Segments::set(int value)
    {
		GetImpObj()->setSegments(value);
    }
    void MathCircle::Draw()
    {
        OdDrawingManager::R()->appendEntity(GetImpObj()->Clone());
    }
}
