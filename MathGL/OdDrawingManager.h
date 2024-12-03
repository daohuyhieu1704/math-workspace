#pragma once
#include <OdBaseObject.h>
#include <OdDbEntity.h>
#include <OdHostAppService.h>
#include <OdJig.h>
#include "OdMathCircle.h"

using PointPickedCallback = void(*)(std::vector<GeometryNative::OdGePoint3d> resPnt);
using EntityPickedCallback = void(*)(const std::vector<OdDbObjectId>& resPnt);

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
	std::vector<OdBaseObjectPtr> getJigs() const { return m_jigs; }
	void appendJig(const OdBaseObjectPtr& jig) { m_jigs.push_back(jig); }
	void setJigs(std::vector<OdBaseObjectPtr>& jigs) { m_jigs = jigs; }
#pragma endregion
	virtual ~OdDrawingManager() = default;
	void CreateSession(std::string fileName);
	void ChangeSession(unsigned int sessionId);
	void AppendCommand(const std::string command);
	void AppendPrompt(const std::string prompt);
	OdBaseObjectPtr getEntityById(unsigned int id)
	{
		if (!OdHostAppService::R()->getCurrentSession()) return OdBaseObjectPtr();
		return OdHostAppService::R()->getCurrentSession()->getEntityById(id);
	}
	int getHistorySize()
	{
		if (!OdHostAppService::R()->getCurrentSession()) return 0;
		return OdHostAppService::R()->getCurrentSession()->getPrompts()->historySize();
	}
	std::string GetCurrentFilePath()
	{
		if (!OdHostAppService::R()->getCurrentSession()) return "";
		return OdHostAppService::R()->getCurrentSession()->getFileName();
	}
	void renderAll();
	std::string m_json = "";

	/// <summary>
	/// Pick-point features
	/// </summary>
	/// <param m_name="callback"></param>
	void SetPointPickedCallback(PointPickedCallback callback);
	void TriggerPointPicked(std::vector<OdGePoint3d> resPnt);

	/// <summary>
	/// Pick-entity features
	///	</summary>
	/// <param m_name="callback"></param>
	void SetEntityPickedCallback(EntityPickedCallback callback);
	void TriggerEntityPicked(const std::vector<OdDbObjectId>& resId);
private:
	OdHostAppServicePtr m_appServices;
	void drawBoundingBox(const OdGeExtents3d& extents);
	std::vector<OdBaseObjectPtr> m_jigs;
	std::vector<const OdBaseObject*> m_tempRenders;
	PointPickedCallback pointPickedCallback = nullptr;
	EntityPickedCallback entityPickedCallback = nullptr;
};
OD_RTTI_DEFINE(OdDrawingManager, OdBaseObject)