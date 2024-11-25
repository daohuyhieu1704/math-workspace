#include "pch.h"
#include "OdMathSession.h"

OD_RTTI_DEFINE(OdMathSession, OdBaseObject)

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
