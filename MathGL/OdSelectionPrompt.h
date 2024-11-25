#pragma once
#include "AbstractSelectionPrompt.h"

typedef OdSmartPtr<class OdSelectionPrompt> OdSelectionPromptPtr;
class OdSelectionPrompt :
    public AbstractSelectionPrompt
{
	OD_RTTI_DECLARE(OdSelectionPrompt, AbstractSelectionPrompt)
	OD_RTTI_SINGLETON_DECLARE(OdSelectionPrompt)
public:
	OdSelectionPrompt();
	virtual ~OdSelectionPrompt() = default;
	OdResult pickObjects(int x, int y) override;
	void resetWorldMouse(int x, int y);
	OdBaseObjectPtr Clone() override;
};
