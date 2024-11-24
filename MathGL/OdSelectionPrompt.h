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
	OdResult pickObjects(int x, int y) override;
	OdBaseObjectPtr Clone() override;
private:
};
