#include "pch.h"
#include "OdHostAppService.h"

OD_RTTI_DEFINE(OdHostAppService, OdBaseObject)
OdHostAppService::OdHostAppService()
{
	m_sessions = std::unordered_map<std::string, OdMathSessionPtr>();
	createSession("Untitled");
};

OdHostAppServicePtr OdHostAppService::getInstance()
{
	static OdHostAppServicePtr instance = OdHostAppService::createObject();
	return instance;
}

OdBaseObjectPtr OdHostAppService::Clone()
{
	return OdHostAppServicePtr();
}
