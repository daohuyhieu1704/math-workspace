#pragma once
#include <Windows.h>
#include "OdBaseObject.h"

class IEngine : public OdBaseObject
{
	OD_RTTI_DECLARE_ABSTRACT(IEngine, OdBaseObject)
public:
	virtual ~IEngine() = default;
	virtual HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd) = 0;
};

OD_RTTI_DEFINE_ABSTRACT(IEngine, OdBaseObject)
