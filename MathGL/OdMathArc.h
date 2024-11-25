#pragma once
#include "OdDbArc.h"

typedef OdSmartPtr<class OdMathArc> MathArcPtr;
class OdMathArc :
    public OdDbArc
{
	OD_RTTI_DECLARE(OdMathArc, OdDbArc)
public:
	OdMathArc();
	OdMathArc(OdGePoint3d startPnt, OdGePoint3d endPnt, double bulge);
	OdResult draw() const override;
    OdBaseObjectPtr Clone() override;
    static void calculateCircleFrom3Points(
        const OdGePoint3d& p1,
        const OdGePoint3d& p2,
        const OdGePoint3d& p3,
        OdGePoint3d& center,
        double& radius);
    static double calculateBulge(const OdGePoint3d& center, const OdGePoint3d& p1, const OdGePoint3d& p2);
private:
	int m_segments = 50;
};

OD_RTTI_DEFINE(OdMathArc, OdDbArc)
