#pragma once
#include "OdDbObject.h"
#include <OdGeScale3d.h>
#include <OdGeExtents3d.h>

using namespace GeometryNative;
using json = nlohmann::json;

class OdDbEntity : public OdDbObject
{
	OD_RTTI_DECLARE_ABSTRACT(OdDbEntity, OdDbObject);
	OdGeScale3d m_scale = OdGeScale3d(1.0, 1.0, 1.0);
	OdGePoint3d m_position = OdGePoint3d::kOrigin;
	OdGeVector3d m_xDir = OdGeVector3d::kXAxis;
	OdGeVector3d m_yDir = OdGeVector3d::kYAxis;
	OdGeVector3d m_zDir = OdGeVector3d::kZAxis;
	OdGeExtents3d m_extents = OdGeExtents3d(OdGePoint3d::kOrigin, OdGePoint3d::kOrigin);
public:
#pragma region Properties
	OdGeScale3d getScale() const { return m_scale; }
	void setScale(const OdGeScale3d& scale) { m_scale = scale; }
	OdGePoint3d getPosition() const { return m_position; }
	void setPosition(const OdGePoint3d& position) { m_position = position; }
	OdGeVector3d getXDir() const { return m_xDir; }
	void setXDir(const OdGeVector3d& xDir) { m_xDir = xDir; }
	OdGeVector3d getYDir() const { return m_yDir; }
	void setYDir(const OdGeVector3d& yDir) { m_yDir = yDir; }
	OdGeVector3d getZDir() const { return m_zDir; }
	void setZDir(const OdGeVector3d& zDir) { m_zDir = zDir; }
	OdGeExtents3d getExtents() const { return m_extents; }
	void setExtents(const OdGeExtents3d& extents) { m_extents = extents; }
#pragma endregion

	virtual OdGeExtents3d boundingBox() const = 0;
	virtual OdResult worldDraw() const = 0;
	virtual json toJson() const;
	virtual void fromJson(const json& j);
};

OD_RTTI_DEFINE_ABSTRACT(OdDbEntity, OdDbObject)

