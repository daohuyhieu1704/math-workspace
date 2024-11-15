#pragma once
#include <OdBaseObject.h>

typedef OdSmartPtr<class OdDrawingManager> OdDrawingManagerPtr;
class OdDrawingManager : public OdBaseObject
{
	OD_RTTI_DECLARE(OdDrawingManager, OdBaseObject)
public:
	HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd);
	// Inherited via OdBaseObject
	OdBaseObjectPtr Clone() override;
};
OD_RTTI_DEFINE(OdDrawingManager, OdBaseObject)