#pragma once
#include "OdMath3dSolid.h"
#include "OdDrawingManager.h"
#include "Entity.h"

using namespace Geometry;

namespace MathGL {
	public ref class Math3dSolid : Entity
	{
	protected:
		OdMath3dSolid* GetImpObj()
		{
			return static_cast<OdMath3dSolid*>(DisposableWrapper::GetImpObj());
		}
	public:
		Math3dSolid()
			: Entity(new OdMath3dSolid(), true)
		{
		}
		void createBox(double x, double y, double z)
		{
			GetImpObj()->createBox(x, y, z);
		}
		void createExtrudeSolid(unsigned int entityId, double height, Vector3d aXis)
		{
			OdGeVector3d nativeAxis(aXis.X, aXis.Y, aXis.Z);
			GetImpObj()->createExtrudeSolid(entityId, height, nativeAxis);
		}
		void createSweepSolid(unsigned int profileId, unsigned int pathId)
		{
			GetImpObj()->createSweepSolid(profileId, pathId);
		}
		// void Draw();
	};
}

