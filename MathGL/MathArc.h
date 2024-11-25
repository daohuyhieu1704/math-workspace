#pragma once
#include "DisposableWrapper.h"
#include "OdMathArc.h"
#include "OdDrawingManager.h"

using namespace Geometry;

namespace MathGL {
	public ref class MathArc : DisposableWrapper
	{
	protected:
		MathArc()
			: DisposableWrapper(IntPtr(new OdMathArc()), true)
		{
		}
		OdMathArc* GetImpObj()
		{
			return static_cast<OdMathArc*>(DisposableWrapper::GetImpObj());
		}
	public:
		MathArc(Point3d startPnt, Point3d endPnt)
			: DisposableWrapper(IntPtr(new OdMathArc()), true)
		{
			OdGePoint3d nativeStart = OdGePoint3d(startPnt.X, startPnt.Y, startPnt.Z);
			OdGePoint3d nativeEnd = OdGePoint3d(endPnt.X, endPnt.Y, endPnt.Z);
			GetImpObj()->setStartPoint(nativeStart);
			GetImpObj()->setEndPoint(nativeEnd);
			GetImpObj()->setBulge(0.0);
		}
		MathArc(Point3d startPnt, Point3d endPnt, Point3d thirdPnt)
			: DisposableWrapper(IntPtr(new OdMathArc()), true)
		{
			OdGePoint3d nativeStart = OdGePoint3d(startPnt.X, startPnt.Y, startPnt.Z);
			OdGePoint3d nativeEnd = OdGePoint3d(endPnt.X, endPnt.Y, endPnt.Z);
			OdGePoint3d nativeThird = OdGePoint3d(thirdPnt.X, thirdPnt.Y, thirdPnt.Z);

			OdGePoint3d center;
			double radius;
			OdMathArc::calculateCircleFrom3Points(nativeStart, nativeEnd, nativeThird, center, radius);

			double bulge = OdMathArc::calculateBulge(center, nativeStart, nativeEnd);

			GetImpObj()->setStartPoint(nativeStart);
			GetImpObj()->setEndPoint(nativeEnd);
			GetImpObj()->setBulge(bulge);
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
		property double Bulge
		{
			double get();
			void set(double value);
		}
		void Draw();
	};
}

