#pragma once
#include <windows.h>
#include "DisposableWrapper.h"
#include "OdDrawingManager.h"

using namespace System;
using namespace System::Collections::Generic;

namespace MathGL {
	public ref class DrawingManager : DisposableWrapper
	{
		static DrawingManager^ m_instance;
		DrawingManager()
			: DisposableWrapper(IntPtr(OdDrawingManager::R().get()), true)
		{
		}
		
	public:
		delegate IntPtr InitializeWindowDelegate(IntPtr parentHandle);
		property static DrawingManager^ Instance
		{
			DrawingManager^ get()
			{
				if (m_instance == nullptr)
					m_instance = gcnew DrawingManager();
				return m_instance;
			}
		}

		IntPtr InitializeWindow(IntPtr parentHandle);
		int ProcessGLUTEvents();
	private:
		OdDrawingManager* GetImpObj()
		{
			return static_cast<OdDrawingManager*>(DisposableWrapper::GetImpObj());
		}
	};
}
