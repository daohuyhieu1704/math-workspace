#include "pch.h"
#include "OdGiDrawable.h"

bool OdGiDrawable::isKindOf(const std::string desc) const
{
    return desc == "OdGiDrawable" || OdBaseObject::isKindOf(desc);
}