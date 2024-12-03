#pragma once
#include <OdDbPlane.h>

typedef OdSmartPtr<class OdMathPlane> OdMathPlanePtr;
class OdMathPlane :
	public OdDbPlane
{
	OD_RTTI_DECLARE(OdMathPlane, OdDbPlane);
	OD_RTTI_REGISTER_CLASS(OdMathPlane);
public:
	OdMathPlane();
	OdResult draw() override;
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

