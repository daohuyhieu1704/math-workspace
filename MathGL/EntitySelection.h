#pragma once
#include "DisposableWrapper.h"
#include "OdDrawingManager.h"
#include "OdSelectionPrompt.h"

using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;

namespace MathGL
{
	public delegate void EntityPickedDelegate(std::vector<OdDbObjectId> resId);
	public delegate void EntitySelectedCallback(List<unsigned int>^ entities);
	public ref class EntitySelection : DisposableWrapper
	{
	public:
		EntitySelection()
			: DisposableWrapper(IntPtr(new OdSelectionPrompt()), true)
		{
		}
		Task<List<unsigned int>^>^ getEntities(int total);

		static property unsigned int LastId
		{
			unsigned int get()
			{
				return OdSelectionPrompt::LastId().GetObjectId();
			}
		}
	private:
		OdSelectionPrompt* GetImpObj()
		{
			return static_cast<OdSelectionPrompt*>(DisposableWrapper::GetImpObj());
		}
		static void OnEntityPicked(std::vector<OdDbObjectId> resId)
		{
			List<unsigned int>^ entities = gcnew List<unsigned int>(resId.size());
			for (int i = 0; i < resId.size(); i++)
			{
				entities->Add(resId[i].GetObjectId());
			}
			_tcs->SetResult(entities);
		}
		static EntityPickedDelegate^ _entityPickedDelegate;
		static TaskCompletionSource<List<unsigned int>^>^ _tcs;
	};
}