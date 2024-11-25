#pragma once
#include <chrono>
#include <queue>
#include <set>
#include <any>
#include <unordered_map>
#include "CommandPrompt.h"

typedef OdSmartPtr<class OdMathSession> OdMathSessionPtr;
class OdMathSession :
    public OdBaseObject
{
    OD_RTTI_DECLARE(OdMathSession, OdBaseObject)
public:
    OdBaseObjectPtr Clone() override;
    OdMathSession();
	std::string getFileName() { return fileName; }
	void setFileName(std::string name) { fileName = name; }
	void undo();
	void redo();
	CommandPromptPtr getPrompts() { return mathPrompt; }
	void ExecuteAllPrompts()
	{
		mathPrompt->executeAllPrompts();
	}
	CommandPromptPtr mathPrompt;
	virtual ~OdMathSession() = default;
private:
	std::string fileName = "";
};