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
	Entity^ DrawingManager::getEntityById(unsigned int id)
	{
		OdBaseObjectPtr entities = GetImpObj()->getEntityById(id);
		if (!entities)
		{
			return nullptr;
		}
		OdDbEntity* entityRaw = static_cast<OdDbEntity*>(entities.get());
		Entity^ entity = gcnew Entity(entityRaw, false);
		return entity;
	}
}