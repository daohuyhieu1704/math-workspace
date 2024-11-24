#pragma once
#include "OdBaseObject.h"
#include "OdResult.h"

class AbstractSelectionPrompt :
    public OdBaseObject
{
	OD_RTTI_DECLARE_ABSTRACT(AbstractSelectionPrompt, OdBaseObject)
public:
    virtual OdResult pickObjects(int x, int y) = 0;

    // Inherited via OdBaseObject
    OdBaseObjectPtr Clone() override;
};

OD_RTTI_DEFINE_ABSTRACT(AbstractSelectionPrompt, OdBaseObject) 