#pragma once
#include "DisposableWrapper.h"
#include "OdMathCircle.h"
#include "OdDrawingManager.h"

using namespace Geometry;

namespace MathGL {
	public ref class MathCircle : DisposableWrapper
	{
	protected:
		MathCircle()
			: DisposableWrapper(IntPtr(new OdMathCircle()), true)
		{
		}
		OdMathCircle* GetImpObj()
		{
			return static_cast<OdMathCircle*>(DisposableWrapper::GetImpObj());
		}
	public:
		MathCircle(Point3d center, double radius)
			: DisposableWrapper(IntPtr(new OdMathCircle()), true)
		{
			OdGePoint3d nativeCenter = OdGePoint3d(center.X, center.Y, center.Z);
			GetImpObj()->setCenter(nativeCenter);
			GetImpObj()->setRadius(radius);
		}
		property Point3d Center
		{
			Point3d get();
			void set(Point3d value);
		}
		property double Radius
		{
			double get();
			void set(double value);
		}
		property int Segments
		{
			int get();
			void set(int value);
		}
		
		void Draw();
	};
}
