#pragma once
#include "OdGePoint2d.h"

namespace Geometry
{
	class OdGeExtend2d
	{
	private:
		OdGePoint2d m_min;
		OdGePoint2d m_max;
	public:
	#pragma region Properties
		OdGePoint2d GetMinPnt() const;
		void SetMinPnt(OdGePoint2d minPnt);
		OdGePoint2d GetMaxPnt() const;
		void SetMaxPnt(OdGePoint2d maxPnt);
	#pragma endregion
	
		OdGeExtend2d(OdGePoint2d minPnt, OdGePoint2d maxPnt);
		~OdGeExtend2d();
	};
}