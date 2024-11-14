#include "pch.h"
#include "OdDbObject.h"

OdDbObjectId OdDbObject::id() const
{
	return getObjectId();
}

json OdDbObject::toJson() const
{
	json j;
	return j;
}

void OdDbObject::fromJson(const json& j)
{
}
