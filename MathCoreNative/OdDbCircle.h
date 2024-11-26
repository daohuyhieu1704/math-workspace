#pragma once
#include "OdDbEntity.h"

typedef OdSmartPtr<class OdDbCircle> OdDbCirclePtr;
class OdDbCircle :
    public OdDbEntity
{
	OD_RTTI_DECLARE(OdDbCircle, OdDbEntity)
public:
	virtual ~OdDbCircle() = default;
	OdDbCircle();
	OdGePoint3d getCenter() const { return m_center; }
	void setCenter(OdGePoint3d center)
	{ 
		m_center = center; 
		setPosition(center);
	}
	double getRadius() const { return m_radius; }
	void setRadius(float radius) { m_radius = radius; }

	// Inherited via OdDbEntity
	OdBaseObjectPtr Clone() override;
	virtual OdResult draw();

	// Inherited via OdDbObject
	virtual json toJson() const override;
	virtual void fromJson(const json& j) override;
private:
	OdGePoint3d m_center;
	double m_radius;
};