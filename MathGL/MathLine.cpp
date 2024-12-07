#include "pch.h"
#include "MathLine.h"
namespace MathGL
{
    Point3d MathLine::StartPnt::get()
    {
        return Point3d(GetImpObj()->getStartPnt().x, GetImpObj()->getStartPnt().y, GetImpObj()->getStartPnt().z);
    }
    void MathLine::StartPnt::set(Point3d value)
    {
        GetImpObj()->setStartPnt(OdGePoint3d(value.X, value.Y, value.Z));
    }
    Point3d MathLine::EndPnt::get()
    {
        return Point3d(GetImpObj()->getEndPnt().x, GetImpObj()->getEndPnt().y, GetImpObj()->getEndPnt().z);
    }
    void MathLine::EndPnt::set(Point3d value)
    {
        GetImpObj()->setEndPnt(OdGePoint3d(value.X, value.Y, value.Z));
    }
    //void MathLine::Draw()
    //{
    //    OdDrawingManager::R()->appendEntity(GetImpObj()->Clone());
    //}
}
