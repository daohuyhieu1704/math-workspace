#pragma once
#include "OdDbEntity.h"

typedef OdSmartPtr<class OdDbPlane> OdDbPlanePtr;
class OdDbPlane :
	public OdDbEntity
{
	OD_RTTI_DECLARE(OdDbPlane, OdDbEntity)
public:
	OdDbPlane();
	virtual ~OdDbPlane() = default;
#pragma region Properties
	OdGePoint3d getOrigin() const { return m_origin; }
	void setOrigin(OdGePoint3d origin) { m_origin = origin; }
	OdGeVector3d getNormal() const { return m_normal; }
	void setNormal(OdGeVector3d normal) { m_normal = normal; }
#pragma endregion

	// Inherited via OdDbEntity
	OdBaseObjectPtr Clone() override;
	virtual OdResult draw();

	// Inherited via OdDbObject
	virtual json toJson() const override;
	virtual void fromJson(const json& j) override;
private:
	OdGePoint3d m_origin;
	OdGeVector3d m_normal = OdGeVector3d::kZAxis;
};