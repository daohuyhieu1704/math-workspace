#pragma once
#include <OdBaseObject.h>
#include <OdDbEntity.h>
#include <OdHostAppService.h>
#include <OdDatabase.h>
#include <OdJig.h>

typedef OdSmartPtr<class OdDrawingManager> OdDrawingManagerPtr;
class OdDrawingManager : public OdBaseObject
{
	OD_RTTI_DECLARE(OdDrawingManager, OdBaseObject)
public:
	OD_RTTI_SINGLETON_DECLARE(OdDrawingManager)
	HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, HWND parentHwnd);
	// Inherited via OdBaseObject
	OdBaseObjectPtr Clone() override;

	void appendEntity(OdBaseObjectPtr entity) { m_entities.push_back(entity); }
	void removeEntity(OdBaseObjectPtr entity) {
		auto it = std::find(m_entities.begin(), m_entities.end(), entity);
		if (it != m_entities.end()) {
			m_entities.erase(it);
		}
	}
	std::vector<OdBaseObjectPtr> getJigs() const { return m_jigs; }
	void setJigs(std::vector<OdBaseObjectPtr>& jigs) { m_jigs = jigs; }

	OdDrawingManager()
	{
		m_database = OdDatabase::createObject();
		RegisterCommandPattern();
	}
	OdTransactionPtr startTransaction()
	{
		return m_database->startTransaction();
	}
	void CreateSession(std::string fileName);
	void ChangeSession(std::string filePath);
	void AppendCommand(const std::string command);
	void AppendPrompt(const std::string prompt);
	void RegisterCommandPattern();
	void pickObject(int x, int y);
private:
	OdDatabasePtr m_database;
	std::map<int, OdBaseObjectPtr> objectMap;
	std::vector<OdBaseObjectPtr> m_entities;
	std::vector<OdBaseObjectPtr> m_jigs;
	std::vector<OdBaseObjectPtr> m_tempRenders;
	static OdDrawingManagerPtr m_instance;
};
OD_RTTI_DEFINE(OdDrawingManager, OdBaseObject)