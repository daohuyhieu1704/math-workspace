#pragma once
#include <OdBaseObject.h>
#include <OdDbEntity.h>
#include <OdHostAppService.h>
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

#pragma region Properties
	std::vector<const OdBaseObject*> getEntities() const { return m_entities; }
	void setEntities(const std::vector<const OdBaseObject*>& entities) { m_entities = entities; }
	void appendEntity(const OdBaseObject* entity) { m_entities.push_back(entity); }
	void removeEntity(const OdBaseObject* entity) { 
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
	}
	std::vector<const OdBaseObject*> getJigs() const { return m_jigs; }
	void setJigs(std::vector<const OdBaseObject*>& jigs) { m_jigs = jigs; }
#pragma endregion
	OdDrawingManager()
	{
		RegisterCommandPattern();
	}
	void CreateSession(std::string fileName);
	void ChangeSession(std::string filePath);
	void AppendCommand(const std::string command);
	void AppendPrompt(const std::string prompt);
	void RegisterCommandPattern();
private:
	std::vector<const OdBaseObject*> m_entities;
	std::vector<const OdBaseObject*> m_jigs;
	std::vector<const OdBaseObject*> m_tempRenders;
	static OdDrawingManagerPtr m_instance;
};
OD_RTTI_DEFINE(OdDrawingManager, OdBaseObject)