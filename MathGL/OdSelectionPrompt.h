#pragma once
#include "AbstractSelectionPrompt.h"
#include <vector>

typedef OdSmartPtr<class OdSelectionPrompt> OdSelectionPromptPtr;
class OdSelectionPrompt :
    public AbstractSelectionPrompt
{
	OD_RTTI_DECLARE(OdSelectionPrompt, AbstractSelectionPrompt)
public:
	OdSelectionPrompt();
	virtual ~OdSelectionPrompt() = default;
	static OdResult pickObjects(int x, int y);
	OdBaseObjectPtr Clone() override;

	using PointPickedCallback = void(*)(OdDbObjectId id);
	OdDbObjectId getObjectId();

	static void resetWorldMouse(int x, int y);
	void Focus();
	static void AppendId(const OdDbObjectId& point);
	static OdDbObjectId LastId();
	static void Clear();
	static void TotalPick(int total);
	static void SetEntityPicked(bool picked);
private:
	static bool m_endPicked;
	static int m_totalPick;
	static std::vector<OdDbObjectId> m_ents;
	static OdDbObjectId m_ent;
};
