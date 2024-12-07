#pragma once
#include "OdDbPolyline.h"

typedef OdSmartPtr<class OdMathPolyline> OdMathPolylinePtr;
class OdMathPolyline :
	public OdDbPolyline
{
	OD_RTTI_DECLARE(OdMathPolyline, OdDbPolyline);
	OD_RTTI_REGISTER_CLASS(OdMathPolyline);
public:
#pragma region Properties
	void setSegments(int segments) { m_segments = segments; }
	int getSegments() const { return m_segments; }
	void setClosed(bool closed) { m_isClosed = closed; }
	bool isClosed() const { return m_isClosed; }
#pragma endregion
	OdMathPolyline();
	virtual ~OdMathPolyline() = default;
	// OdMathPolyline(OdGePoint3d center, double radius);
	OdBaseObjectPtr Clone() override;
	OdResult draw() override;
private:
	bool m_isClosed = false;
	void drawArc(const OdGePoint3d& start, const OdGePoint3d& end, double bulge) const;
	int m_segments = 100;
};
OD_RTTI_DEFINE(OdMathPolyline, OdDbPolyline)