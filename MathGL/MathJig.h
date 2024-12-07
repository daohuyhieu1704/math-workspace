#pragma once
#include "OdJig.h"
#include "OdBaseObject.h"
#include "OdGePoint3d.h"
#include "DisposableWrapper.h"

using namespace Geometry;

namespace MathGL
{
    public enum class DragStatus
    {
        Normal = 0,
        Cancel = 1,
        Other = 2,
        NoChange = 3
    };

    public ref class MathJig abstract : public DisposableWrapper
    {
    protected:
        MathJig()
            : DisposableWrapper(IntPtr::Zero, false)
        {
        }

        MathJig(IntPtr nativePtr)
            : DisposableWrapper(nativePtr, true)
        {
        }

        virtual OdJig* GetImpObj() abstract;

    public:
        // virtual OdBaseObject^ Entity() = 0;

        virtual DragStatus Sampler() = 0;

        virtual bool Update() = 0;

        virtual bool Preview() = 0;

        virtual DragStatus AcquirePoint(Point3d point) = 0;
    };
}
