#pragma once

#include "DisposableWrapper.h"
#include "OdDbEntity.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace Geometry;

namespace MathGL
{
    public ref class Entity : public DisposableWrapper
    {
    protected:
        OdDbEntity* GetImpObj()
        {
            return static_cast<OdDbEntity*>(DisposableWrapper::GetImpObj());
        }
    public:
        Entity(OdDbEntity* nativeEntity, bool autoDelete) : DisposableWrapper(IntPtr(nativeEntity), autoDelete)
        {
        }
        property Scale3d Scale
        {
            Scale3d get();
            void set(Scale3d value);
        }

        property Point3d Position
        {
            Point3d get();
            void set(Point3d value);
        }

        property Vector3d XDir
        {
            Vector3d get();
            void set(Vector3d value);
        }

        property Vector3d YDir
        {
            Vector3d get();
            void set(Vector3d value);
        }

        property Vector3d ZDir
        {
            Vector3d get();
            void set(Vector3d value);
        }

        property Matrix3d Transform
        {
            Matrix3d get();
        }

        property bool IsVisible
        {
            bool get();
            void set(bool value);
        }

        property bool IsSelected
        {
            bool get();
            void set(bool value);
        }

        property Extents3d Extents
        {
            Extents3d get();
        }

        OdResult TransformBy(Matrix3d xform);
        virtual String^ ToJson();
        virtual void FromJson(String^ json);
    };
}

