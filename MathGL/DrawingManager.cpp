#include "pch.h"
#include "DrawingManager.h"
namespace MathGL
{
	IntPtr DrawingManager::InitializeWindow(IntPtr parentHandle)
	{
		HINSTANCE hInstance = GetModuleHandle(nullptr);
		HWND m_hwnd = GetImpObj()->InitializeWindow(hInstance, SW_SHOW, static_cast<HWND>(parentHandle.ToPointer()));
		return IntPtr(m_hwnd);
	}
}