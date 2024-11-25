#pragma once
#include "AbstractSelectionPrompt.h"
#include <OdDbEntity.h>

typedef OdSmartPtr<class OdPointPrompt> OdPointPromptPtr;
class OdPointPrompt :
	public AbstractSelectionPrompt
{
	OD_RTTI_DECLARE(OdPointPrompt, AbstractSelectionPrompt)
public:
	OdPointPrompt();
	virtual ~OdPointPrompt() = default;
	OdBaseObjectPtr Clone() override;

	using PointPickedCallback = void(*)(double x, double y, double z);
	OdGePoint3d getPoints();
	void Focus();
	static void AppendPoint(const OdGePoint3d point);
	static OdGePoint3d LastPoint();
	static void Clear();
	static void TotalPick(int total);
	static void SetEntityPicked(bool picked);
private:
	static bool pointPicked;
	static int m_totalPick;
	static std::vector<OdGePoint3d> m_points;
	static OdGePoint3d m_lastPoint;
};

OD_RTTI_DEFINE(OdPointPrompt, AbstractSelectionPrompt)

