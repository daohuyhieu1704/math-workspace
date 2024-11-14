#pragma once
#include "OdBaseObject.h"
#include "OdResult.h"

class OdGiDrawable : public OdBaseObject {
    OD_RTTI_DECLARE_ABSTRACT(OdGiDrawable, OdBaseObject)
public:
    virtual ~OdGiDrawable() = default;

    virtual OdResult draw() const = 0;
};

OD_RTTI_DEFINE_ABSTRACT(OdGiDrawable, OdBaseObject)