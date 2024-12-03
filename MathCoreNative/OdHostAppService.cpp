#include "pch.h"
#include "OdHostAppService.h"
#include "OdBaseObject.h"

OD_RTTI_DEFINE(OdHostAppService, OdBaseObject)
OD_RTTI_SINGLETON_DEFINE(OdHostAppService)

OdHostAppService::OdHostAppService()
{
	m_sessions = std::unordered_map<unsigned int, OdMathSessionPtr>();
	currentSessionId = 0;
};

OdBaseObjectPtr OdHostAppService::Clone()
{
	return OdHostAppServicePtr();
}
