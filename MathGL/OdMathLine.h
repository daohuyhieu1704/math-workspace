#pragma once
#include "OdDbLine.h"

typedef OdSmartPtr<class OdMathLine> OdMathLinePtr;
class OdMathLine :
    public OdDbLine
{
	OD_RTTI_DECLARE(OdMathLine, OdDbLine);
	OD_RTTI_REGISTER_CLASS(OdMathLine);
public:
	OdMathLine();
	OdMathLine(OdGePoint3d startPnt, OdGePoint3d endPnt);
	OdResult draw() override;
	OdBaseObjectPtr Clone() override;
	virtual ~OdMathLine() = default;
};

OD_RTTI_DEFINE(OdMathLine, OdDbLine)

