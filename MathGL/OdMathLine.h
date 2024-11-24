#pragma once
#include "OdDbLine.h"

typedef OdSmartPtr<class OdMathLine> OdMathLinePtr;
class OdMathLine :
    public OdDbLine
{
	OD_RTTI_DECLARE(OdMathLine, OdDbLine);	
public:
	OdMathLine();
	OdMathLine(OdGePoint3d startPnt, OdGePoint3d endPnt);
	OdResult draw() const override;
};

OD_RTTI_DEFINE(OdMathLine, OdDbLine)

