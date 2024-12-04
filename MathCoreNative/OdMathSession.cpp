#include "pch.h"
#include "OdMathSession.h"
#include "OdDbEntity.h"

OdBaseObjectPtr OdMathSession::getEntityById(unsigned int id)
{
	for (const auto& entity : m_entities)
	{
		OdDbEntity* objRaw = static_cast<OdDbEntity*>(entity.get());
		unsigned int entId = objRaw->id();
		if (entId == id)
		{
			return OdBaseObjectPtr(entity);
		}
	}
	return OdBaseObjectPtr();
}

void OdMathSession::removeEntity(unsigned int id)
{
	m_entities.erase(
		std::remove_if(m_entities.begin(), m_entities.end(),
			[id](const OdBaseObjectPtr& objBase) {
				OdDbEntity* entity = static_cast<OdDbEntity*>(objBase.get());
				if (!entity) return false;
				return entity->id() == id;
			}),
		m_entities.end());
}

OdBaseObjectPtr OdMathSession::Clone()
{
	return OdMathSessionPtr();
}

OdMathSession::OdMathSession()
{
}