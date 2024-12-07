#pragma once
#include "OdDb3dSolid.h"
#include <opencascade/TopoDS_Shape.hxx>

typedef OdSmartPtr<class OdMath3dSolid> OdMath3dSolidPtr;
class OdMath3dSolid :
	public OdDb3dSolid
{
	OD_RTTI_DECLARE(OdMath3dSolid, OdDb3dSolid);
	OD_RTTI_REGISTER_CLASS(OdMath3dSolid);
public:
	OdMath3dSolid();
	OdResult draw() override;
	OdBaseObjectPtr Clone() override;
	virtual ~OdMath3dSolid() = default;
	virtual OdResult createBox(double x, double y, double z);
	virtual OdResult createExtrudeSolid(unsigned int entityId, double height, OdGeVector3d aXis);
	virtual OdResult createSweepSolid(unsigned int profileId, unsigned int pathId);
private:
	void extractGeometry(const TopoDS_Shape& shape);
	TopoDS_Shape m_shape;
	virtual OdResult calculateVolume() override;
	virtual OdResult calculateSurfaceArea() override;
};

OD_RTTI_DEFINE(OdMath3dSolid, OdDb3dSolid)

