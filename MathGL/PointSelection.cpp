#include "pch.h"
#include "PointSelection.h"

namespace MathGL
{
    Task<List<Point3d>^>^ PointSelection::getPoints(int total)
    {
        OdPointPrompt::Clear();
        OdPointPrompt::TotalPick(total);
        OdPointPrompt::SetPointPicked(true);
        _tcs = gcnew TaskCompletionSource<List<Point3d>^>();
        _pointPickedDelegate = gcnew PointPickedDelegate(&PointSelection::OnPointPicked);
        IntPtr ptr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_pointPickedDelegate);
        OdDrawingManager::R()->SetPointPickedCallback(static_cast<PointPickedCallback>(ptr.ToPointer()));
        return _tcs->Task;
    }
}
