#include "pch.h"
#include "MathPlane.h"

namespace MathGL {
	Point3d MathPlane::Origin::get()
	{
		OdGePoint3d pnt = GetImpObj()->getOrigin();
		return Point3d(pnt.x, pnt.y, pnt.z);
	}
	void MathPlane::Origin::set(Point3d value)
	{
		OdGePoint3d pnt = OdGePoint3d(value.X, value.Y, value.Z);
		GetImpObj()->setOrigin(pnt);
	}
	Vector3d MathPlane::Normal::get()
	{
		OdGeVector3d pnt = GetImpObj()->getNormal();
		return Vector3d(pnt.x, pnt.y, pnt.z);
	}
	void MathPlane::Normal::set(Vector3d value)
	{
		OdGeVector3d pnt = OdGeVector3d(value.X, value.Y, value.Z);
		GetImpObj()->setNormal(pnt);
	}
	//void MathPlane::Draw()
	//{
	//	OdDrawingManager::R()->appendEntity(GetImpObj()->Clone());
	//}
}