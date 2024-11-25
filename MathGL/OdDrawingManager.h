#pragma once
#include <OdBaseObject.h>
#include <OdDbEntity.h>
#include <OdHostAppService.h>
#include <OdJig.h>
#include "OdMathCircle.h"

using PointPickedCallback = void(*)(std::vector<GeometryNative::OdGePoint3d> resPnt);
using EntityPickedCallback = void(*)();

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
	std::vector<OdBaseObjectPtr> getEntities() const { return m_entities; }
	void setEntities(std::vector<OdBaseObjectPtr>& entities) { m_entities = entities; }
	void appendEntity(const OdBaseObjectPtr& entity) { m_entities.push_back(entity); }
	int appendEntity(std::string m_name);
	OdBaseObjectPtr& getEntityAt(int index) { return m_entities[index]; }
	void removeEntity(const OdBaseObjectPtr& entity) { m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end()); }
	std::vector<OdBaseObjectPtr> getJigs() const { return m_jigs; }
	void appendJig(const OdBaseObjectPtr& jig) { m_jigs.push_back(jig); }
	void setJigs(std::vector<OdBaseObjectPtr>& jigs) { m_jigs = jigs; }
#pragma endregion
	virtual ~OdDrawingManager() = default;
	OdDrawingManager()
	{
	}
	void CreateSession(std::string fileName);
	void ChangeSession(std::string filePath);
	void AppendCommand(const std::string command);
	void AppendPrompt(const std::string prompt);
	void RegisterCommandPattern();
	void renderAll();
	json m_json;

	/// <summary>
	/// Pick-point features
	/// </summary>
	/// <param m_name="callback"></param>
	void SetPointPickedCallback(PointPickedCallback callback);
	void TriggerPointPicked(std::vector<OdGePoint3d> resPnt);
	void SetEntityPickedCallback(EntityPickedCallback callback);
	void TriggerEntityPicked();
private:
	std::vector<OdBaseObjectPtr> m_entities;
	std::vector<OdBaseObjectPtr> m_jigs;
	std::vector<const OdBaseObject*> m_tempRenders;
	PointPickedCallback pointPickedCallback = nullptr;
	EntityPickedCallback entityPickedCallback = nullptr;
};
OD_RTTI_DEFINE(OdDrawingManager, OdBaseObject)