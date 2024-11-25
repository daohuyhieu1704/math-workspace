#pragma once
#include "OdDbEntity.h"

typedef OdSmartPtr<class OdDbArc> OdDbArcPtr;
class OdDbArc : public OdDbEntity
{
	OD_RTTI_DECLARE(OdDbArc, OdDbEntity)
public:
	OdDbArc();
	virtual ~OdDbArc() = default;
#pragma region Properties
	double getBulge() const { return m_bulge; }
	void setBulge(double bulge) { m_bulge = bulge; }

	OdGePoint3d getStartPoint() const { return m_startPnt; }
	void setStartPoint(const OdGePoint3d& point) { 
		m_startPnt = point;
		setPosition(m_startPnt);
	}

	OdGePoint3d getEndPoint() const { return m_endPnt; }
	void setEndPoint(const OdGePoint3d& point) { m_endPnt = point; }
#pragma endregion

	// Inherited via OdDbEntity
	OdBaseObjectPtr Clone() override;
	virtual OdResult draw() const;
	virtual OdGeExtents3d boundingBox() const;
	OdResult worldDraw() const override;

	// Inherited via OdDbObject
	virtual json toJson() const override;
	virtual void fromJson(const json& j) override;
private:
	double m_bulge;
	OdGePoint3d m_startPnt;
	OdGePoint3d m_endPnt;
};

OD_RTTI_DEFINE(OdDbArc, OdDbEntity)
