#pragma once
#include <OdDbPlane.h>

typedef OdSmartPtr<class MathPlane> MathPlanePtr;
class MathPlane :
	public OdDbPlane
{
	OD_RTTI_DECLARE(MathPlane, OdDbPlane)
public:
	MathPlane();
	OdResult draw() const override;
private:
	void drawNormalVector(
		OdGePoint3d origin,
		OdGeVector3d normal,
		OdGeVector3d u,
		OdGeVector3d v,
		double planeSize
	) const;
};

OD_RTTI_DEFINE(MathPlane, OdDbPlane)

