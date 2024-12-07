#include "pch.h"
#include "OdBaseObject.h"

std::unordered_map<std::string, OdObjectFactory::CreateFunction> OdObjectFactory::m_registry;

OdDbObjectId OdBaseObject::getObjectId() const
{
	return m_id;
}
