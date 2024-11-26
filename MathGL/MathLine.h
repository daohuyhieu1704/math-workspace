#pragma once
#include "OdMathLine.h"
#include "OdDrawingManager.h"
#include "Entity.h"

using namespace Geometry;

namespace MathGL {
	public ref class MathLine : Entity
	{
	protected:
		MathLine()
			: Entity(new OdMathLine(), true)
		{
		}
		OdMathLine* GetImpObj()
		{
			return static_cast<OdMathLine*>(DisposableWrapper::GetImpObj());
		}
	public:
		MathLine(Point3d startPnt, Point3d endPnt)
			: Entity(new OdMathLine(), true)
		{
			OdGePoint3d nativeStart = OdGePoint3d(startPnt.X, startPnt.Y, startPnt.Z);
			OdGePoint3d nativeEnd = OdGePoint3d(endPnt.X, endPnt.Y, endPnt.Z);
			GetImpObj()->setStartPnt(nativeStart);
			GetImpObj()->setEndPnt(nativeEnd);
		}
		property Point3d StartPnt
		{
			Point3d get();
			void set(Point3d value);
		}
		property Point3d EndPnt
		{
			Point3d get();
			void set(Point3d value);
		}
		void Draw();
	};
}
