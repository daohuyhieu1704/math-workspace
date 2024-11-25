#pragma once
#include <OdDbPlane.h>

typedef OdSmartPtr<class OdMathPlane> OdMathPlanePtr;
class OdMathPlane :
	public OdDbPlane
{
	OD_RTTI_DECLARE(OdMathPlane, OdDbPlane)
public:
	OdMathPlane();
	OdResult draw() const override;
	OdBaseObjectPtr Clone() override;
	virtual ~OdMathPlane() = default;
private:
	void drawNormalVector(
		OdGePoint3d origin,
		OdGeVector3d normal,
		OdGeVector3d u,
		OdGeVector3d v,
		double planeSize
	) const;
};

OD_RTTI_DEFINE(OdMathPlane, OdDbPlane)

