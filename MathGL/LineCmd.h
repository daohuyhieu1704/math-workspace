#pragma once
#include "IActionCmd.h"
#include "OdGePoint3d.h"

using namespace GeometryNative;

typedef OdSmartPtr<class LineCmd> LineCmdPtr;
class LineCmd :
    public IActionCmd
{
	OD_RTTI_DECLARE(LineCmd, IActionCmd);

	// Inherited via IActionCmd
	OdBaseObjectPtr Clone() override;
	bool execute() override;
	bool serialize(const std::vector<std::string>& strData) override;
	virtual ~LineCmd() = default;
private:
	OdGePoint3d startPnt;
	OdGePoint3d endPnt;
};

OD_RTTI_DEFINE(LineCmd, IActionCmd)

