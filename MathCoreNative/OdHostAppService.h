#pragma once
#include "OdMathSession.h"

typedef OdSmartPtr<class OdHostAppService> OdHostAppServicePtr;
class OdHostAppService :
    public OdBaseObject
{
	OD_RTTI_DECLARE(OdHostAppService, OdBaseObject)
public:
	OD_RTTI_SINGLETON_DECLARE(OdHostAppService)
	OdMathSessionPtr createSession() {
		OdMathSessionPtr session = OdMathSession::createObject();
		unsigned int sessionId = session->getObjectId().GetObjectId();
		if (m_sessions.find(sessionId) != m_sessions.end()) {
			return m_sessions[sessionId];
		}
		m_sessions[sessionId] = OdMathSessionPtr(session);
		currentSessionId = sessionId;
		return session;
	}

	OdMathSessionPtr getSession(unsigned int sessionId) {
		if (m_sessions.find(sessionId) != m_sessions.end()) {
			return m_sessions[sessionId];
		}
		return OdMathSessionPtr();
	}

	void ChangeCurrSession(unsigned int sessionId) {
		if (m_sessions.find(sessionId) != m_sessions.end()) {
			currentSessionId = sessionId;
		}
	}
	void removeSession(unsigned int sessionId) {
		m_sessions.erase(sessionId);
	}

	OdMathSessionPtr getCurrentSession() {
		if (currentSessionId == 0) return OdMathSessionPtr();
		return getSession(currentSessionId);
	}
	unsigned int getCurrentSessionId() const {
		return currentSessionId;
	}
	// Inherited via OdBaseObject
	OdBaseObjectPtr Clone() override;
	OdHostAppService();
private:
	virtual ~OdHostAppService() = default;
	OdHostAppService(const OdHostAppService&) = delete;
	OdHostAppService& operator=(const OdHostAppService&) = delete;
	std::unordered_map<unsigned int, OdMathSessionPtr> m_sessions;
	unsigned int currentSessionId;
};