#pragma once
#include "OdDbLine.h"

typedef OdSmartPtr<class MathLine> MathLinePtr;
class MathLine :
    public OdDbLine
{
	OD_RTTI_DECLARE(MathLine, OdDbLine);	
public:
	MathLine();
	MathLine(OdGePoint3d startPnt, OdGePoint3d endPnt);
	OdResult draw() const override;
};

OD_RTTI_DEFINE(MathLine, OdDbLine)

