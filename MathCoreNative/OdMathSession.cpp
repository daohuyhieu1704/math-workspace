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

OdBaseObjectPtr OdMathSession::Clone()
{
	return OdMathSessionPtr();
}

OdMathSession::OdMathSession()
{
    mathPrompt = CommandPrompt::createObject();
}
  
void OdMathSession::undo()
{
	mathPrompt->undo();
}

void OdMathSession::redo()
{
	mathPrompt->redo();
}
