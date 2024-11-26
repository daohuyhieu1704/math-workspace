#include "pch.h"
#include "MathPolyline.h"

namespace MathGL
{
    void MathPolyline::AddVertex(Point3d vertex)
    {
        OdGePoint3d nativePnt = OdGePoint3d(vertex.X, vertex.Y, vertex.Z);
        GetImpObj()->addVertex(nativePnt, 0);
    }

    void MathPolyline::AddVertex(Point3d vertex, double bulge)
    {
        OdGePoint3d nativePnt = OdGePoint3d(vertex.X, vertex.Y, vertex.Z);
        GetImpObj()->addVertex(nativePnt, bulge);
    }

    Point3d MathPolyline::GetVertexAt(int index)
    {
        OdGePoint3d pnt = GetImpObj()->getVertexAt(index);
        return Point3d(pnt.x, pnt.y, pnt.z);
    }

    double MathPolyline::GetBulgeAt(int index)
    {
        return GetImpObj()->getBulgeAt(index);
    }

    int MathPolyline::NumVerts::get()
    {
        return GetImpObj()->numVertices();
    }

    bool MathPolyline::IsClosed::get()
    {
        return GetImpObj()->isClosed();
    }

    void MathPolyline::IsClosed::set(bool value)
    {
        GetImpObj()->setClosed(value);
    }

    void MathPolyline::Draw()
    {
        OdDrawingManager::R()->appendEntity(GetImpObj()->Clone());
    }
}