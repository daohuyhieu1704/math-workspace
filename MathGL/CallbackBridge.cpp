#include "pch.h"
#include "CallbackBridge.h"

namespace MathGL {
	void CallbackBridge::RegisterMouseCallback(MouseClickCallback^ callback)
	{
		mouseCallback = callback;
	}

	//void NotifyMouseClick(int x, int y) {
	//	// Dereference mouseCallback to compare the actual managed object
	//	if (mouseCallback.operator->() != nullptr) {
	//		mouseCallback->Invoke(x, y); // Call the managed delegate
	//	}
	//}
}