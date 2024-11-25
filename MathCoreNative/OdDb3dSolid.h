#pragma once
#include "OdDbEntity.h"

enum class SolidType
{
	Box,
	Cylinder,
	Cone,
	Sphere,
	Torus,
	Prism,
	Pyramid,
	Extrusion,
	Revolution
};

typedef OdSmartPtr<class OdDb3dSolid> OdDb3dSolidPtr;
class OdDb3dSolid :
	public OdDbEntity
{
	OD_RTTI_DECLARE(OdDb3dSolid, OdDbEntity);
public:
	OdDb3dSolid();
#pragma region Getters and Setters
	std::string getName() const { return m_name; }
	void setName(const std::string& name) { m_name = name; }

	std::string getMaterial() const { return m_material; }
	void setMaterial(const std::string& material) { m_material = material; }

	double getVolume() const { return m_volume; }
	double getSurfaceArea() const { return m_surfaceArea; }

	SolidType getType() const { return m_type; }
	void setType(SolidType type) { this->m_type = type; }
#pragma endregion

	virtual ~OdDb3dSolid() = default;
	// Inherited via OdDbEntity
	OdBaseObjectPtr Clone() override;
	virtual OdResult draw() const;
	OdGeExtents3d boundingBox() const override;
	OdResult worldDraw() const override;

	// Inherited via OdDbObject
	virtual json toJson() const override;
	virtual void fromJson(const json& j) override;
private:
	SolidType m_type;
	std::string m_name;
	std::string m_material;
	double m_volume;
	double m_surfaceArea;
protected:
	virtual OdResult calculateVolume();
	virtual OdResult calculateSurfaceArea();
};

OD_RTTI_DEFINE(OdDb3dSolid, OdDbEntity)	

