#pragma once
#include "DisposableWrapper.h"
#include "OdMathPolyline.h"

using namespace Geometry;

namespace MathGL
{
    public ref class MathPolyline :
        public DisposableWrapper
    {
    protected:
        MathPolyline()
            : DisposableWrapper(IntPtr(new OdMathPolyline()), true)
        {
        }
        OdMathPolyline* GetImpObj()
        {
            return static_cast<OdMathPolyline*>(DisposableWrapper::GetImpObj());
        }
    public:
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
    };
}