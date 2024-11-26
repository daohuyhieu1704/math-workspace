#include "pch.h"
#include "OdHostAppService.h"
#include "OdBaseObject.h"

OD_RTTI_DEFINE(OdHostAppService, OdBaseObject)
OD_RTTI_SINGLETON_DEFINE(OdHostAppService)

OdHostAppService::OdHostAppService()
{
	m_sessions = std::unordered_map<std::string, OdMathSessionPtr>();
	createSession("Untitled");
};

OdBaseObjectPtr OdHostAppService::Clone()
{
	return OdHostAppServicePtr();
}
