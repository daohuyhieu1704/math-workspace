#include "pch.h"
#include "OdDbObject.h"

unsigned int OdDbObject::id() const
{
	return getObjectId().GetObjectId();
}

json OdDbObject::toJson() const
{
	json j;
	return j;
}

void OdDbObject::fromJson(const json& j)
{
}
