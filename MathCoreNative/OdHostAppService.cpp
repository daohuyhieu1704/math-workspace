#include "pch.h"
#include "OdHostAppService.h"

OdHostAppServicePtr OdHostAppService::m_instance;

OD_RTTI_DEFINE(OdHostAppService, OdBaseObject)
OdHostAppService::OdHostAppService()
{
	m_sessions = std::unordered_map<std::string, OdMathSessionPtr>();
	createSession("Untitled");
};

OdHostAppServicePtr OdHostAppService::getInstance()
{
	if (m_instance.isNull())
	{
		m_instance = OdHostAppService::createObject();
	}
	return m_instance;
}

OdBaseObjectPtr OdHostAppService::Clone()
{
	return OdHostAppServicePtr();
}
