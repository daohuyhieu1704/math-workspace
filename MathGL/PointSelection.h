#pragma once
#include "DisposableWrapper.h"
#include "OdMathCircle.h"
#include "OdDrawingManager.h"
#include "OdPointPrompt.h"

using namespace Geometry;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;

namespace MathGL
{
	public delegate void PointPickedDelegate(std::vector<GeometryNative::OdGePoint3d> resPnt);
	public delegate void PointsSelectedCallback(List<Point3d>^ points);

	public ref class PointSelection : DisposableWrapper
	{
	public:
		PointSelection()
			: DisposableWrapper(IntPtr(new OdPointPrompt()), true)
		{
		}
		Task<List<Point3d>^>^ getPoints(int total);
	private:
		OdPointPrompt* GetImpObj()
		{
			return static_cast<OdPointPrompt*>(DisposableWrapper::GetImpObj());
		}
		static void OnPointPicked(std::vector<GeometryNative::OdGePoint3d> resPnt)
		{
			List<Point3d>^ points = gcnew List<Point3d>(resPnt.size());
			for (int i = 0; i < resPnt.size(); i++)
			{
				points->Add(Point3d(resPnt[i].x, resPnt[i].y, 0.0));
			}

			_tcs->SetResult(points);
		}
		static PointPickedDelegate^ _pointPickedDelegate;
		static TaskCompletionSource<List<Point3d>^>^ _tcs;
	};
}
