#pragma once
#include <windows.h>

using namespace System;

namespace MathGL {
	public ref class GLEngineNative
	{
		static GLEngineNative^ m_instance;
		GLEngineNative()
		{
		}
		HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd);
	public:
		property static GLEngineNative^ Instance
		{
			GLEngineNative^ get()
			{
				if (m_instance == nullptr)
					m_instance = gcnew GLEngineNative();
				return m_instance;
			}
		}
		IntPtr InitializeWindow(IntPtr parentHandle);
		int ProcessGLUTEvents();
	};
}
