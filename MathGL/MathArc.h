#pragma once
#include "OdDbArc.h"

typedef OdSmartPtr<class MathArc> MathArcPtr;
class MathArc :
    public OdDbArc
{
	OD_RTTI_DECLARE(MathArc, OdDbArc)
public:
	MathArc();
	MathArc(OdGePoint3d startPnt, OdGePoint3d endPnt, double bulge);
	OdResult draw() const override;
private:
	int m_segments = 50;
};

OD_RTTI_DEFINE(MathArc, OdDbArc)
