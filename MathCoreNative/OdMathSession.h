#pragma once
#include <chrono>
#include <queue>
#include <set>
#include <any>
#include <unordered_map>
#include <stack>
#include "OdBaseObject.h"

typedef OdSmartPtr<class OdMathSession> OdMathSessionPtr;
class OdMathSession :
    public OdBaseObject
{
    OD_RTTI_DECLARE(OdMathSession, OdBaseObject)
public:
	std::vector<OdBaseObjectPtr> getEntities() const { return m_entities; }
	OdBaseObjectPtr getEntityById(unsigned int id);
	void setEntities(std::vector<OdBaseObjectPtr>& entities) { m_entities = entities; }
	unsigned int appendEntity(const OdBaseObjectPtr& entity) {
		m_entities.push_back(entity);
		return entity->getObjectId().GetObjectId();
	}
	OdBaseObjectPtr& getEntityAt(int index) { return m_entities[index]; }
	void removeEntity(const OdBaseObjectPtr& entity) { 
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end()); 
	}
	void removeEntity(unsigned int id);
    OdBaseObjectPtr Clone() override;
	std::string getFileName() { return fileName; }
	void setFileName(std::string m_name) { fileName = m_name; }
	OdMathSession();
	virtual ~OdMathSession() = default;
private:
	std::vector<OdBaseObjectPtr> m_entities;
	std::string fileName = "";
};

OD_RTTI_DEFINE(OdMathSession, OdBaseObject)