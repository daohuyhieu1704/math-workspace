#pragma once
#include <vcclr.h>

namespace MathGL
{
	public delegate void MouseClickCallback(int x, int y);
	static gcroot<MouseClickCallback^> mouseCallback;
	public ref class CallbackBridge
	{
	public:
		static void RegisterMouseCallback(MouseClickCallback^ callback);
	};
};

extern "C" __declspec(dllexport) void NotifyMouseClick(int x, int y) {
	if (MathGL::mouseCallback.operator->() != nullptr) {
		MathGL::mouseCallback->Invoke(x, y);
	}
}