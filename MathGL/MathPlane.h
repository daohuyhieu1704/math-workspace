#pragma once
#include "Entity.h"
#include "OdMathPlane.h"
#include "OdDrawingManager.h"


using namespace Geometry;

namespace MathGL {
	public ref class MathPlane : Entity
	{
	protected:
		OdMathPlane* GetImpObj()
		{
			return static_cast<OdMathPlane*>(DisposableWrapper::GetImpObj());
		}
	public:
		MathPlane()
			: Entity(new OdMathPlane(), true)
		{
		}
		MathPlane(IntPtr unmanagedPointer, bool autoDelete)
			: Entity(unmanagedPointer, autoDelete)
		{
		}
		MathPlane(Point3d origin, Vector3d normal)
			: Entity(new OdMathPlane(), true)
		{
			OdGePoint3d org = OdGePoint3d(origin.X, origin.Y, origin.Z);
			OdGeVector3d norm = OdGeVector3d(normal.X, normal.Y, normal.Z);
			GetImpObj()->setOrigin(org);
			GetImpObj()->setNormal(norm);
		}
		property Point3d Origin
		{
			Point3d get();
			void set(Point3d value);
		}
		property Vector3d Normal
		{
			Vector3d get();
			void set(Vector3d value);
		}
		// void Draw();
	};
}