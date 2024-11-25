#include "pch.h"
#include "EntitySelection.h"

Task<List<unsigned int>^>^ MathGL::EntitySelection::getEntities(int total)
{
	OdSelectionPrompt::Clear();
	OdSelectionPrompt::TotalPick(total);
	OdSelectionPrompt::SetEntityPicked(true);
	_tcs = gcnew TaskCompletionSource<List<unsigned int>^>();
	_entityPickedDelegate = gcnew EntityPickedDelegate(&EntitySelection::OnEntityPicked);
	IntPtr ptr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_entityPickedDelegate);
	OdDrawingManager::R()->SetEntityPickedCallback(static_cast<EntityPickedCallback>(ptr.ToPointer()));
	return _tcs->Task;
}
