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
	void appendEntity(const OdBaseObjectPtr& entity) {
		m_entities.push_back(entity);
	}
	std::vector<OdBaseObjectPtr> getEntities() { return m_entities; }

	void removeEntity(const OdBaseObjectPtr& entity) {
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
	}
	CommandPromptPtr getPrompts() { return mathPrompt; }
	void ExecuteAllPrompts()
	{
		mathPrompt->executeAllPrompts();
	}
	CommandPromptPtr mathPrompt;
private:
	std::vector<OdBaseObjectPtr> m_entities;
	std::string fileName = "";
};

OD_RTTI_DEFINE(OdMathSession, OdBaseObject)