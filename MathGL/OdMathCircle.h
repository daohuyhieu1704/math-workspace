#pragma once
#include "OdDbCircle.h"

typedef OdSmartPtr<class OdMathCircle> OdMathCirclePtr;
class OdMathCircle :
    public OdDbCircle
{
	OD_RTTI_DECLARE(OdMathCircle, OdDbCircle);
public:
#pragma region Properties
	void setSegments(int segments) { m_segments = segments; }
	int getSegments() const { return m_segments; }
#pragma endregion
	OdMathCircle();
	OdMathCircle(OdGePoint3d center, double radius);
	OdBaseObjectPtr Clone() override;
	OdResult draw() const override;
	virtual ~OdMathCircle() = default;
private:
	int m_segments = 100;
};
OD_RTTI_DEFINE(OdMathCircle, OdDbCircle)
