#pragma once
#include "Entity.h"
#include "OdMathPolyline.h"
#include "OdDrawingManager.h"

using namespace Geometry;

namespace MathGL
{
    public ref class MathPolyline :
        public Entity
    {
    protected:
        OdMathPolyline* GetImpObj()
        {
            return static_cast<OdMathPolyline*>(DisposableWrapper::GetImpObj());
        }
    public:
        MathPolyline()
            : Entity(new OdMathPolyline(), true)
        {
        }
        void AddVertex(Point3d vertex);
        void AddVertex(Point3d vertex, double bulge);
        Point3d GetVertexAt(int index);
        double GetBulgeAt(int index);
        property int NumVerts
        {
            int get();
        }
        property bool IsClosed
        {
            bool get();
            void set(bool value);
        }
        // void Draw();
    };
}