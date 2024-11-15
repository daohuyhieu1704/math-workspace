#pragma once
#include <windows.h>

using namespace System;

namespace MathGL {
	public ref class GLEngineController
	{
		static GLEngineController^ m_instance;
		GLEngineController()
		{
		}
		HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd);
	public:
		property static GLEngineController^ Instance
		{
			GLEngineController^ get()
			{
				if (m_instance == nullptr)
					m_instance = gcnew GLEngineController();
				return m_instance;
			}
		}
		IntPtr InitializeWindow(IntPtr parentHandle);
		int ProcessGLUTEvents();
	};
}
