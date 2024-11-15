#pragma once
#include "OdDbCircle.h"

typedef OdSmartPtr<class MathCircle> MathCirclePtr;
class MathCircle :
    public OdDbCircle
{
	OD_RTTI_DECLARE(MathCircle, OdDbCircle);
public:
#pragma region Properties
	void setSegments(int segments) { m_segments = segments; }
	int getSegments() const { return m_segments; }
#pragma endregion
	MathCircle();
	MathCircle(OdGePoint3d center, double radius);
	OdResult draw() const override;
private:
	int m_segments = 100;
};
OD_RTTI_DEFINE(MathCircle, OdDbCircle)
