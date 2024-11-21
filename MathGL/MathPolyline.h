#pragma once
#include "OdDbPolyline.h"

typedef OdSmartPtr<class MathPolyline> MathPolylinePtr;
class MathPolyline :
	public OdDbPolyline
{
	OD_RTTI_DECLARE(MathPolyline, OdDbPolyline);
public:
#pragma region Properties
	void setSegments(int segments) { m_segments = segments; }
	int getSegments() const { return m_segments; }
#pragma endregion
	MathPolyline();
	// MathPolyline(OdGePoint3d center, double radius);
	OdResult draw() const override;
private:
	void drawArc(const OdGePoint3d& start, const OdGePoint3d& end, double bulge) const;
	int m_segments = 100;
};
OD_RTTI_DEFINE(MathPolyline, OdDbPolyline)